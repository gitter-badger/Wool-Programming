using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Browser_test
{
	public partial class Form1 : Form
	{
		private string first_url = "https://www.google.co.jp/?gws_rd=ssl";
		public Form1()
		{
			InitializeComponent();
			webBrowser1.Navigate(first_url);
		}

		private void webBrowser1_Navigating(object sender, WebBrowserNavigatingEventArgs e)
		{
			tabPage1.Text = "読み込み中";
		}

		private void webBrowser1_Navigated(object sender, WebBrowserNavigatedEventArgs e)
		{
			URLtext.Text = webBrowser1.Url.ToString();
			tabPage1.Text = webBrowser1.DocumentTitle;
		}

		private void button1_Click(object sender, EventArgs e)
		{
			webBrowser1.GoBack();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			webBrowser1.GoForward();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			webBrowser1.Refresh();
		}

		private void webBrowser1_NewWindow(object sender, CancelEventArgs e)
		{
			WebBrowser wb = (WebBrowser)sender;
			webBrowser1.Navigate(wb.StatusText);
			e.Cancel = true;
		}

		private void URLtext_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				webBrowser1.Navigate(URLtext.Text);
			}

		}

		private void button4_Click(object sender, EventArgs e)
		{
			webBrowser1.Navigate(URLtext.Text);
		}
	}
}
