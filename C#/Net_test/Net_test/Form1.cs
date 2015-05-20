using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net.NetworkInformation;
using System.Net;

namespace Net_test
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void getDefaultGateway()
		{
			NetworkInterface[] adapters = NetworkInterface.GetAllNetworkInterfaces();
			foreach (NetworkInterface nic in adapters)
			{
				IPInterfaceProperties ipInfo = nic.GetIPProperties();
				GatewayIPAddressInformationCollection gatewayaddress = ipInfo.GatewayAddresses;
				IPAddressCollection dnsadd = ipInfo.DnsAddresses;
				IPAddressCollection dhcpadd = ipInfo.DhcpServerAddresses;
				string netname = nic.Name.ToString();

				if (netname.Contains("Wi-Fi"))
				{
					textBox1.AppendText("名称		: " + nic.Name + Environment.NewLine);
					textBox1.AppendText("説明		: " + nic.Description + Environment.NewLine);
					textBox1.AppendText("I/F種類		: " + nic.NetworkInterfaceType.ToString() + Environment.NewLine);
					textBox1.AppendText("最大速度		: " + (nic.Speed / 1000000).ToString() + "Mbps" + Environment.NewLine);
					textBox1.AppendText("macアドレス	: " + nic.GetPhysicalAddress().ToString() + Environment.NewLine);
					textBox1.AppendText("送信byte数	: " + nic.GetIPv4Statistics().BytesSent.ToString() + Environment.NewLine);
					textBox1.AppendText("受信byte数	: " + nic.GetIPv4Statistics().BytesReceived.ToString() + Environment.NewLine);
					textBox1.AppendText("IPアドレス		: " + ipInfo.UnicastAddresses[1].Address.ToString() + Environment.NewLine);
					foreach (GatewayIPAddressInformation gaway in gatewayaddress)
					{
						textBox1.AppendText("デフォルトゲートウェイ	: " + gaway.Address.ToString() + Environment.NewLine);
					}
					foreach (IPAddress ipip in dnsadd)
					{
						textBox1.AppendText("IPv4 DNSサーバ	: " + ipip.ToString() + Environment.NewLine);
					}
					foreach (IPAddress iipp in dhcpadd)
					{
						textBox1.AppendText("IPv4 DHCPサーバ	: " + iipp.ToString() + Environment.NewLine);
					}
					//textBox1.AppendText("-----------------------------------" + Environment.NewLine);
					//string hostname = Dns.GetHostName();
					//IPAddress[] hostip = Dns.GetHostAddresses(hostname);
					//IPHostEntry hostentry = Dns.GetHostEntry(hostname);
					//foreach (IPAddress ip in hostip)
					//{
					//	textBox1.AppendText(": " + ip.ToString()+Environment.NewLine);
					//}
				}
			}
		}

		private void GetIpCollec()
		{
			NetworkInterface[] adapters = NetworkInterface.GetAllNetworkInterfaces();
			foreach (NetworkInterface nic in adapters)
			{
				IPInterfaceProperties ipInfo = nic.GetIPProperties();
				GatewayIPAddressInformationCollection gatewayaddress = ipInfo.GatewayAddresses;
				IPAddressCollection dnsadd = ipInfo.DnsAddresses;
				IPAddressCollection dhcpadd = ipInfo.DhcpServerAddresses;
				string netname = nic.Name.ToString();

				if (netname.Contains("Wi-Fi"))
				{
					textBox1.AppendText("名称		: " + nic.Name + Environment.NewLine);
					textBox1.AppendText("説明		: " + nic.Description + Environment.NewLine);
					textBox1.AppendText("I/F種類		: " + nic.NetworkInterfaceType.ToString() + Environment.NewLine);
					textBox1.AppendText("最大速度		: " + (nic.Speed / 1000000).ToString() + "Mbps" + Environment.NewLine);
					textBox1.AppendText("macアドレス	: " + nic.GetPhysicalAddress().ToString() + Environment.NewLine);
					textBox1.AppendText("IPv4アドレス	: " + ipInfo.UnicastAddresses[1].Address.ToString() + Environment.NewLine);
					textBox1.AppendText("IPv6アドレス	: " + ipInfo.UnicastAddresses[0].Address.ToString() + Environment.NewLine);
					foreach (GatewayIPAddressInformation gaway in gatewayaddress)
					{
						textBox1.AppendText("デフォルトゲートウェイ	: " + gaway.Address.ToString() + Environment.NewLine);
					}
					foreach (IPAddress ipip in dnsadd)
					{
						textBox1.AppendText("IPv4 DNSサーバ	: " + ipip.ToString() + Environment.NewLine);
					}
					foreach (IPAddress iipp in dhcpadd)
					{
						textBox1.AppendText("IPv4 DHCPサーバ	: " + iipp.ToString() + Environment.NewLine);
					}
				}
			}
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			textBox1.Clear();
			getDefaultGateway();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if (!checkBox1.Checked)
				timer1.Start();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			timer1.Stop();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void checkBox1_CheckedChanged(object sender, EventArgs e)
		{
			if (checkBox1.Checked)
			{
				timer1.Stop();
				textBox1.Clear();
				GetIpCollec();
			}
		}
	}
}
