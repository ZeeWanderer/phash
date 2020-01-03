using Manina.Windows.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace dup_viewer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            string[] allfiles = Directory.GetFiles("./out/", "*.dup", SearchOption.AllDirectories);

            gui_lv_in_files.Columns.Add("Files", -2, HorizontalAlignment.Left);

            gui_lv_in_files.FullRowSelect = true;
            gui_lv_in_files.GridLines = true;

            gui_lv_in_files.View = System.Windows.Forms.View.Details;


            foreach (var file in allfiles.Reverse())
            {
                gui_lv_in_files.Items.Add(file);
            }

        }

        private void file_selected(object sender, EventArgs e)
        {

            if (gui_lv_in_files.SelectedItems.Count == 0) return;

            var selected = gui_lv_in_files.SelectedItems[0].Text;

            var duplicates_p = File.ReadAllLines(selected);

            gui_il_duplicates.SuspendLayout();
            gui_il_duplicates.Items.Clear();

            foreach (var path in duplicates_p.Reverse())
            {
                ImageListViewItem item = new ImageListViewItem(path);
                gui_il_duplicates.Items.Add(item);
            }
            gui_il_duplicates.ResumeLayout();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string[] allfiles = Directory.GetFiles("./out/", "*.dup", SearchOption.AllDirectories);

            if (gui_lv_in_files.SelectedItems.Count == 0) 
            {
                gui_il_duplicates.SuspendLayout();
                gui_il_duplicates.Items.Clear();


                gui_il_duplicates.ResumeLayout();

            }
            else
            {
                var selected = gui_lv_in_files.SelectedItems[0].Text;

                var duplicates_p = File.ReadAllLines(selected);

                gui_il_duplicates.SuspendLayout();
                gui_il_duplicates.Items.Clear();

                foreach (var path in duplicates_p.Reverse())
                {
                    ImageListViewItem item = new ImageListViewItem(path);
                    gui_il_duplicates.Items.Add(item);
                }
                gui_il_duplicates.ResumeLayout();
            }

            gui_lv_in_files.Items.Clear();

            foreach (var file in allfiles.Reverse())
            {
                gui_lv_in_files.Items.Add(file);
            }


        }
    }
}
