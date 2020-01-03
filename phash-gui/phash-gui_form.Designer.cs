namespace phash_gui
{
    partial class PhashGUI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.process1 = new System.Diagnostics.Process();
            this.gui_lv_in_files = new System.Windows.Forms.ListView();
            this.gui_cb_hash = new System.Windows.Forms.ComboBox();
            this.gui_tb_size = new System.Windows.Forms.TrackBar();
            this.gui_l_size = new System.Windows.Forms.Label();
            this.gui_pb_in_image = new System.Windows.Forms.PictureBox();
            this.gui_il_duplicates = new Manina.Windows.Forms.ImageListView();
            this.gui_b_find_duplicates = new System.Windows.Forms.Button();
            this.gui_tb_bit_error_rate = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.gui_cb_error_type = new System.Windows.Forms.ComboBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.gui_tb_size)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gui_pb_in_image)).BeginInit();
            this.SuspendLayout();
            // 
            // process1
            // 
            this.process1.StartInfo.Domain = "";
            this.process1.StartInfo.LoadUserProfile = false;
            this.process1.StartInfo.Password = null;
            this.process1.StartInfo.StandardErrorEncoding = null;
            this.process1.StartInfo.StandardOutputEncoding = null;
            this.process1.StartInfo.UserName = "";
            this.process1.SynchronizingObject = this;
            // 
            // gui_lv_in_files
            // 
            this.gui_lv_in_files.HideSelection = false;
            this.gui_lv_in_files.Location = new System.Drawing.Point(12, 12);
            this.gui_lv_in_files.MultiSelect = false;
            this.gui_lv_in_files.Name = "gui_lv_in_files";
            this.gui_lv_in_files.Size = new System.Drawing.Size(322, 659);
            this.gui_lv_in_files.TabIndex = 0;
            this.gui_lv_in_files.UseCompatibleStateImageBehavior = false;
            this.gui_lv_in_files.SelectedIndexChanged += new System.EventHandler(this.file_selected);
            // 
            // gui_cb_hash
            // 
            this.gui_cb_hash.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.gui_cb_hash.FormattingEnabled = true;
            this.gui_cb_hash.Location = new System.Drawing.Point(340, 12);
            this.gui_cb_hash.Name = "gui_cb_hash";
            this.gui_cb_hash.Size = new System.Drawing.Size(121, 21);
            this.gui_cb_hash.TabIndex = 2;
            this.gui_cb_hash.SelectedIndexChanged += new System.EventHandler(this.gui_cb_hash_SelectedIndexChanged);
            // 
            // gui_tb_size
            // 
            this.gui_tb_size.Location = new System.Drawing.Point(516, 12);
            this.gui_tb_size.Maximum = 128;
            this.gui_tb_size.Minimum = 8;
            this.gui_tb_size.Name = "gui_tb_size";
            this.gui_tb_size.Size = new System.Drawing.Size(642, 45);
            this.gui_tb_size.TabIndex = 3;
            this.gui_tb_size.Value = 8;
            this.gui_tb_size.Scroll += new System.EventHandler(this.gui_tb_size_Scroll);
            // 
            // gui_l_size
            // 
            this.gui_l_size.AutoSize = true;
            this.gui_l_size.Location = new System.Drawing.Point(467, 15);
            this.gui_l_size.Name = "gui_l_size";
            this.gui_l_size.Size = new System.Drawing.Size(24, 13);
            this.gui_l_size.TabIndex = 4;
            this.gui_l_size.Text = "8x8";
            // 
            // gui_pb_in_image
            // 
            this.gui_pb_in_image.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.gui_pb_in_image.Location = new System.Drawing.Point(340, 52);
            this.gui_pb_in_image.Name = "gui_pb_in_image";
            this.gui_pb_in_image.Size = new System.Drawing.Size(272, 265);
            this.gui_pb_in_image.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.gui_pb_in_image.TabIndex = 5;
            this.gui_pb_in_image.TabStop = false;
            // 
            // gui_il_duplicates
            // 
            this.gui_il_duplicates.Location = new System.Drawing.Point(340, 323);
            this.gui_il_duplicates.Name = "gui_il_duplicates";
            this.gui_il_duplicates.PersistentCacheDirectory = "";
            this.gui_il_duplicates.PersistentCacheSize = ((long)(100));
            this.gui_il_duplicates.Size = new System.Drawing.Size(818, 348);
            this.gui_il_duplicates.TabIndex = 6;
            this.gui_il_duplicates.UseWIC = true;
            // 
            // gui_b_find_duplicates
            // 
            this.gui_b_find_duplicates.Location = new System.Drawing.Point(618, 90);
            this.gui_b_find_duplicates.Name = "gui_b_find_duplicates";
            this.gui_b_find_duplicates.Size = new System.Drawing.Size(114, 23);
            this.gui_b_find_duplicates.TabIndex = 7;
            this.gui_b_find_duplicates.Text = "Find Duplicates";
            this.gui_b_find_duplicates.UseVisualStyleBackColor = true;
            this.gui_b_find_duplicates.Click += new System.EventHandler(this.file_selected);
            // 
            // gui_tb_bit_error_rate
            // 
            this.gui_tb_bit_error_rate.Location = new System.Drawing.Point(619, 64);
            this.gui_tb_bit_error_rate.Name = "gui_tb_bit_error_rate";
            this.gui_tb_bit_error_rate.Size = new System.Drawing.Size(100, 20);
            this.gui_tb_bit_error_rate.TabIndex = 8;
            this.gui_tb_bit_error_rate.Text = "0.21";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(618, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Bit Error Rate:";
            // 
            // gui_cb_error_type
            // 
            this.gui_cb_error_type.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.gui_cb_error_type.FormattingEnabled = true;
            this.gui_cb_error_type.Location = new System.Drawing.Point(725, 64);
            this.gui_cb_error_type.Name = "gui_cb_error_type";
            this.gui_cb_error_type.Size = new System.Drawing.Size(121, 21);
            this.gui_cb_error_type.TabIndex = 10;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(1058, 63);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 11;
            this.textBox1.Text = "0.21";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(618, 120);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 12;
            this.label2.Text = "label2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(618, 148);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "label3";
            // 
            // PhashGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1170, 683);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.gui_cb_error_type);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.gui_tb_bit_error_rate);
            this.Controls.Add(this.gui_b_find_duplicates);
            this.Controls.Add(this.gui_il_duplicates);
            this.Controls.Add(this.gui_pb_in_image);
            this.Controls.Add(this.gui_l_size);
            this.Controls.Add(this.gui_tb_size);
            this.Controls.Add(this.gui_cb_hash);
            this.Controls.Add(this.gui_lv_in_files);
            this.Name = "PhashGUI";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.gui_tb_size)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gui_pb_in_image)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Diagnostics.Process process1;
        private System.Windows.Forms.ListView gui_lv_in_files;
        private System.Windows.Forms.ComboBox gui_cb_hash;
        private System.Windows.Forms.Label gui_l_size;
        private System.Windows.Forms.TrackBar gui_tb_size;
        private System.Windows.Forms.PictureBox gui_pb_in_image;
        private Manina.Windows.Forms.ImageListView gui_il_duplicates;
        private System.Windows.Forms.Button gui_b_find_duplicates;
        private System.Windows.Forms.TextBox gui_tb_bit_error_rate;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox gui_cb_error_type;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
    }
}

