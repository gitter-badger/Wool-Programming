#include "SSerial.h"
//using namespace boost::asio;
using namespace std;

#if 1
int main(){
	string sendstr;
	char str[32];
	int len;
	SSerial sserial;
	sserial.open("COM4");
	sserial.baudrate_set(115200);

	if (!sserial.is_open()){
		cerr << "error" << endl;
	}
	else{
		while (1){
			cin >> sendstr;
			sserial.write(sendstr);
			if (sendstr == "end")
				break;
			cout << "send to " << sendstr << endl;
		}
	}
}
#endif

#if 0

int main(){
	char readstr[32];
	SSerial sserial;
	sserial.PortOpen("COM4");
	sserial.BaudRateSet(9600);
	io_service io;
	serial_port port(io);
	boost::system::error_code e;
	port.open("COM4", e);
	if (e){
		cerr << e << endl;
	}
	port.set_option(serial_port_base::baud_rate(9600));
	port.set_option(serial_port_base::character_size(8));
	port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
	port.set_option(serial_port_base::parity(serial_port_base::parity::none));
	port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
	boost::thread thrio(boost::bind(&io_service::run, &io));
	port.async_read_some(buffer(readstr), boost::bind(&read_callback, _1, _2, boost::ref(readstr)));
	return 0;
}
#endif