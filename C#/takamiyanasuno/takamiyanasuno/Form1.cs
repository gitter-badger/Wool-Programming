using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace takamiyanasuno
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void showpresen()
		{
			MessageBox.Show("「高宮なすのです！」\nBlu-ray１巻\n8/28 発売");
		}

		private void button1_Click(object sender, EventArgs e)
		{
			showpresen();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			showpresen();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			showpresen();
		}
	}
}
