#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\thread.hpp>
#include <iostream>

class SSerial{

public:
	
	SSerial() : ssport(io){
	}

	void baudrate_set(int baud);
	void character_size_set(int charsize);
	void flow_control_set(int flow);
	void parity_set(int parity);
	void stop_bits_set(int stopbits);
	//void open(std::string portname);
	void open(std::string portname, int baud, int charsize, int flow, int parity, int stopbits);
	void close();
	void write(std::string str);
	bool is_open();
	char* read();

	~SSerial(){
		if (ssport.is_open()){
			ssport.close();
			std::cout << "close" << std::endl;
		}
	}
	
private:
	boost::asio::io_service io;
	boost::asio::serial_port ssport;
	char readstr[32];
};

void SSerial::baudrate_set(int baud = 115200){
	ssport.set_option(boost::asio::serial_port_base::baud_rate(baud));
}

void SSerial::character_size_set(int charsize = 8){
	ssport.set_option(boost::asio::serial_port_base::character_size(8));
}

void SSerial::flow_control_set(int flow = 0){
	switch (flow){
		 default:
			ssport.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
			break;
		case 1:
			ssport.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::software));
			break;
		case 2:
			ssport.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::hardware));
			break;
	}
}

void SSerial::parity_set(int parity = 0){
	switch (parity){
		default:
			ssport.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
			break;
		case 1:
			ssport.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::odd));
			break;
		case 2:
			ssport.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::even));
			break;
	}
}

void SSerial::stop_bits_set(int stopbits = 0){
	switch (stopbits){
		default:
			ssport.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
			break;
		case 1:
			ssport.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::onepointfive));
			break;
		case 2:
			ssport.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::two));
			break;
	}
}

//void SSerial::open(std::string portname){
//	boost::system::error_code err;
//	ssport.open(portname, err);
//	if (err){
//		std::cerr << "Port Open Error : " << err.message() << std::endl;
//		return;
//	}
//	ssport.set_option(boost::asio::serial_port_base::character_size(8));
//	ssport.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
//	ssport.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
//	ssport.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
//	boost::thread thr_io(boost::bind(&boost::asio::io_service::run, &io));
//}

void SSerial::open(std::string portname, int baud = 9600, int charsize = 8, int flow = 0, int parity = 0, int stopbits = 0){
	boost::system::error_code err;
	ssport.open(portname, err);
	if (err){
		std::cerr << "Port Open Error : " << err.message() << std::endl;
		return;
	}
	baudrate_set(baud);
	character_size_set(charsize);
	flow_control_set(flow);
	parity_set(parity);
	stop_bits_set(stopbits);
	boost::thread thr_io(boost::bind(&boost::asio::io_service::run, &io));
}

void SSerial::close(){
	ssport.close();
}

void SSerial::write(std::string str){
	ssport.write_some(boost::asio::buffer(str));
}

bool SSerial::is_open(){
	return ssport.is_open();
}

char* SSerial::read(){
	ssport.read_some(boost::asio::buffer(readstr));
	return readstr;
}