using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Net.NetworkInformation;

namespace chat_test
{
	public partial class Form1 : Form
	{
		private UdpClient udp;
		private Encoding encoding;
		private Thread recevethread;
		//private byte[] sendBytes;

		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Udp_init();
			Encoding_init();
			get_ip();
		}

		private void Udp_init()
		{
			udp = new UdpClient(6000);
			udp.DontFragment = true;
			udp.EnableBroadcast = true;
		}

		private void Encoding_init()
		{
			encoding = Encoding.UTF8;
		}

		private void button1_Click(object sender, EventArgs e)
		{
			Send_text();
		}

		private void Send_text()
		{
			try
			{
				if (SendTextBox.Text!=string.Empty)
				{
					byte[] sendBytes = encoding.GetBytes(SendTextBox.Text);
					SendTextBox.Clear();
					udp.Send(sendBytes, sendBytes.Length, SendIPtext.Text, 6000);
					textshow(encoding.GetString(sendBytes) + " : My Message");
				}
			}
			catch (Exception ex)
			{
				textshow("Send Error");
				return;
			}
		}

		private void Receive_start()
		{
			IPEndPoint remoteEP = null;
			while (udp != null)
			{
				try
				{
					if (udp.Available > 0)
					{
						byte[] recvByte = udp.Receive(ref remoteEP);
						textshow(encoding.GetString(recvByte) + " : " + remoteEP.Address.ToString());
					}
				}
				catch (Exception ex)
				{
					textshow("受信失敗");
				}
				Thread.Sleep(100);
			}
		}

		private void checkBox1_CheckedChanged(object sender, EventArgs e)
		{
			if (checkBox1.Checked)
			{
				try
				{
					if (udp == null)
					{
						Udp_init();
						Encoding_init();
					}
					if (recevethread == null)
					{
						recevethread = new Thread(Receive_start);
						recevethread.Start();
					}
				}
				catch (Exception ex)
				{
					textshow("接続失敗");
					checkBox1.Checked = false;
					return;
				}
				textshow("Network Open");
			}
			else
			{
				try
				{
					if (udp != null)
					{
						udp.Close();
						udp = null;
					}
					if (recevethread != null)
					{
						recevethread.Abort();
						recevethread = null;
					}
				}
				catch (Exception ex)
				{
					textshow("Network Close Error");
					checkBox1.Checked = true;
					return;
				}
				textshow("Network Closed");
			}
		}

		private void Form1_FormClosed(object sender, FormClosedEventArgs e)
		{
			if (recevethread != null)
			{
				recevethread.Abort();
			}
			if (udp != null)
			{
				udp.Close();
				udp = null;
			}
		}

		private void textshow(string str)
		{
			CharLogtext.HideSelection = false;
			CharLogtext.AppendText(str+"\r\n");
			//textBox1.Text += str + "\r\n";
		}

		private void get_ip()
		{
			NetworkInterface[] adapters = NetworkInterface.GetAllNetworkInterfaces();
			foreach (NetworkInterface nic in adapters)
			{
				IPInterfaceProperties ipInfo = nic.GetIPProperties();
				string netname = nic.Name.ToString();
				if (netname.Contains("Wi-Fi"))
				{
					MyIPtext.Text = ipInfo.UnicastAddresses[1].Address.ToString();
				}
			}
		}

		private void button2_Click(object sender, EventArgs e)
		{
			CharLogtext.Clear();
		}

		private void SendTextBox_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Enter)
			{
				Send_text();
			}
		}
	}
}
