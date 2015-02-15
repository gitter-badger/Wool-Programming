using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ito
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Calc_Click(object sender, EventArgs e)
		{
			try
			{
				if (comboBox1.SelectedIndex == 0)
				{
					double input1 = double.Parse(textBox1.Text);
					double input2 = double.Parse(textBox2.Text);
					double ans = input1 + input2;
					textBox3.Text = ans.ToString();
				}
				else if (comboBox1.SelectedIndex == 1)
				{
					double input1 = double.Parse(textBox1.Text);
					double input2 = double.Parse(textBox2.Text);
					double ans = input1 - input2;
					textBox3.Text = ans.ToString();
				}
				else if (comboBox1.SelectedIndex == 2)
				{
					double input1 = double.Parse(textBox1.Text);
					double input2 = double.Parse(textBox2.Text);
					double ans = input1 * input2;
					textBox3.Text = ans.ToString();
				}
				else if (comboBox1.SelectedIndex == 3)
				{
					double input1 = double.Parse(textBox1.Text);
					double input2 = double.Parse(textBox2.Text);
					double ans = input1 / input2;
					textBox3.Text = ans.ToString();
				}
				label2.Text = "";
			}
			catch (System.FormatException ex)
			{
				label2.Text = "数値を入力してください";
			}
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			comboBox1.SelectedIndex = 0;
		}
	}
}
