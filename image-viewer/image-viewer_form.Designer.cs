﻿namespace image_viewer
{
    partial class Form1
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
            this.button1 = new System.Windows.Forms.Button();
            this.gui_lv_in_files = new System.Windows.Forms.ListView();
            this.gui_pb_in_image = new System.Windows.Forms.PictureBox();
            this.button2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.gui_pb_in_image)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(239, -61);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 11;
            this.button1.Text = "Reload";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // gui_lv_in_files
            // 
            this.gui_lv_in_files.HideSelection = false;
            this.gui_lv_in_files.Location = new System.Drawing.Point(12, 39);
            this.gui_lv_in_files.MultiSelect = false;
            this.gui_lv_in_files.Name = "gui_lv_in_files";
            this.gui_lv_in_files.Size = new System.Drawing.Size(322, 544);
            this.gui_lv_in_files.TabIndex = 10;
            this.gui_lv_in_files.UseCompatibleStateImageBehavior = false;
            this.gui_lv_in_files.SelectedIndexChanged += new System.EventHandler(this.file_selected);
            // 
            // gui_pb_in_image
            // 
            this.gui_pb_in_image.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.gui_pb_in_image.Location = new System.Drawing.Point(340, 39);
            this.gui_pb_in_image.Name = "gui_pb_in_image";
            this.gui_pb_in_image.Size = new System.Drawing.Size(544, 544);
            this.gui_pb_in_image.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.gui_pb_in_image.TabIndex = 12;
            this.gui_pb_in_image.TabStop = false;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(12, 10);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 13;
            this.button2.Text = "Reload";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1062, 673);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.gui_pb_in_image);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.gui_lv_in_files);
            this.Name = "Form1";
            this.Text = "image-viewer";
            ((System.ComponentModel.ISupportInitialize)(this.gui_pb_in_image)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ListView gui_lv_in_files;
        private System.Windows.Forms.PictureBox gui_pb_in_image;
        private System.Windows.Forms.Button button2;
    }
}

