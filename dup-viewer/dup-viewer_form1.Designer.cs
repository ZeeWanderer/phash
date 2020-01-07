namespace dup_viewer
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
            this.gui_lv_in_files = new System.Windows.Forms.ListView();
            this.button1 = new System.Windows.Forms.Button();
            this.gui_il_duplicates = new Manina.Windows.Forms.ImageListView();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // gui_lv_in_files
            // 
            this.gui_lv_in_files.HideSelection = false;
            this.gui_lv_in_files.Location = new System.Drawing.Point(12, 38);
            this.gui_lv_in_files.MultiSelect = false;
            this.gui_lv_in_files.Name = "gui_lv_in_files";
            this.gui_lv_in_files.Size = new System.Drawing.Size(322, 659);
            this.gui_lv_in_files.TabIndex = 1;
            this.gui_lv_in_files.UseCompatibleStateImageBehavior = false;
            this.gui_lv_in_files.SelectedIndexChanged += new System.EventHandler(this.file_selected);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 9);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Reload";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // gui_il_duplicates
            // 
            this.gui_il_duplicates.Location = new System.Drawing.Point(340, 12);
            this.gui_il_duplicates.Name = "gui_il_duplicates";
            this.gui_il_duplicates.PersistentCacheDirectory = "";
            this.gui_il_duplicates.PersistentCacheSize = ((long)(100));
            this.gui_il_duplicates.Size = new System.Drawing.Size(818, 685);
            this.gui_il_duplicates.TabIndex = 7;
            this.gui_il_duplicates.UseWIC = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(93, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(69, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Duplicates: 0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1179, 703);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.gui_il_duplicates);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.gui_lv_in_files);
            this.Name = "Form1";
            this.Text = "dup-viewer";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView gui_lv_in_files;
        private System.Windows.Forms.Button button1;
        private Manina.Windows.Forms.ImageListView gui_il_duplicates;
        private System.Windows.Forms.Label label1;
    }
}

