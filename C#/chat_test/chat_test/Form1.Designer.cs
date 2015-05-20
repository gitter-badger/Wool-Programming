namespace chat_test
{
	partial class Form1
	{
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナーで生成されたコード

		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.checkBox1 = new System.Windows.Forms.CheckBox();
			this.SendIPtext = new System.Windows.Forms.TextBox();
			this.MyIPtext = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.CharLogtext = new System.Windows.Forms.TextBox();
			this.SendTextBox = new System.Windows.Forms.TextBox();
			this.button2 = new System.Windows.Forms.Button();
			this.panel1 = new System.Windows.Forms.Panel();
			this.panel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(482, 3);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(113, 75);
			this.button1.TabIndex = 0;
			this.button1.Text = "send";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// checkBox1
			// 
			this.checkBox1.AutoSize = true;
			this.checkBox1.Location = new System.Drawing.Point(12, 39);
			this.checkBox1.Name = "checkBox1";
			this.checkBox1.Size = new System.Drawing.Size(66, 16);
			this.checkBox1.TabIndex = 2;
			this.checkBox1.Text = "Network";
			this.checkBox1.UseVisualStyleBackColor = true;
			this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
			// 
			// SendIPtext
			// 
			this.SendIPtext.Location = new System.Drawing.Point(363, 37);
			this.SendIPtext.Name = "SendIPtext";
			this.SendIPtext.Size = new System.Drawing.Size(100, 19);
			this.SendIPtext.TabIndex = 3;
			// 
			// MyIPtext
			// 
			this.MyIPtext.Location = new System.Drawing.Point(230, 37);
			this.MyIPtext.Name = "MyIPtext";
			this.MyIPtext.Size = new System.Drawing.Size(100, 19);
			this.MyIPtext.TabIndex = 4;
			this.MyIPtext.Text = "My IPAddress";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(139, 40);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(76, 12);
			this.label1.TabIndex = 5;
			this.label1.Text = "My IPAddress";
			// 
			// CharLogtext
			// 
			this.CharLogtext.Location = new System.Drawing.Point(12, 118);
			this.CharLogtext.Multiline = true;
			this.CharLogtext.Name = "CharLogtext";
			this.CharLogtext.ReadOnly = true;
			this.CharLogtext.Size = new System.Drawing.Size(760, 431);
			this.CharLogtext.TabIndex = 1;
			// 
			// SendTextBox
			// 
			this.SendTextBox.Location = new System.Drawing.Point(12, 93);
			this.SendTextBox.Name = "SendTextBox";
			this.SendTextBox.Size = new System.Drawing.Size(759, 19);
			this.SendTextBox.TabIndex = 6;
			this.SendTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.SendTextBox_KeyDown);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(681, 3);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 75);
			this.button2.TabIndex = 7;
			this.button2.Text = "LogClear";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.button2);
			this.panel1.Controls.Add(this.button1);
			this.panel1.Location = new System.Drawing.Point(12, 9);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(759, 78);
			this.panel1.TabIndex = 8;
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(784, 561);
			this.Controls.Add(this.SendTextBox);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.MyIPtext);
			this.Controls.Add(this.SendIPtext);
			this.Controls.Add(this.checkBox1);
			this.Controls.Add(this.panel1);
			this.Controls.Add(this.CharLogtext);
			this.Name = "Form1";
			this.Text = "Form1";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
			this.Load += new System.EventHandler(this.Form1_Load);
			this.panel1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.CheckBox checkBox1;
		private System.Windows.Forms.TextBox SendIPtext;
		private System.Windows.Forms.TextBox MyIPtext;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox CharLogtext;
		private System.Windows.Forms.TextBox SendTextBox;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Panel panel1;
	}
}

