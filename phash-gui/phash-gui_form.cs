using Manina.Windows.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace phash_gui
{
    public partial class PhashGUI : Form
    {
        private static List<string> hash_dataSource = new List<string>() {"cosine","simple","median", "diff"};
        private static List<string> error_type_dataSource = new List<string>() { "ber", "mer"};

        private string error_type = error_type_dataSource.First();
        private string hash = hash_dataSource.First();
        private int size = 8;
        private string in_file = "";

        private string out_path_file = "";

        private bool doUpdate = false;

        public PhashGUI()
        {
            InitializeComponent();

            string[] allfiles = Directory.GetFiles("./in/", "*.*", SearchOption.AllDirectories);

            gui_lv_in_files.Columns.Add("Files", -2, HorizontalAlignment.Left);

            gui_lv_in_files.FullRowSelect = true;
            gui_lv_in_files.GridLines = true;
            
            gui_lv_in_files.View = System.Windows.Forms.View.Details;


            foreach (var file in allfiles.Reverse())
            {
                gui_lv_in_files.Items.Add(file);
            }

            gui_cb_hash.DataSource = hash_dataSource;
            gui_cb_error_type.DataSource = error_type_dataSource;
        }

        private void gui_tb_size_Scroll(object sender, EventArgs e)
        {
            var value = gui_tb_size.Value.ToString();
            gui_l_size.Text = value + "x" + value;
            doUpdate = true;
        }

        private void file_selected(object sender, EventArgs e)
        {

            if (gui_lv_in_files.SelectedItems.Count == 0) return;

            var selected = gui_lv_in_files.SelectedItems[0].Text;
            //if (selected == in_file && !doUpdate)
            //    return;

            gui_lv_in_files.Enabled = false;
            gui_b_find_duplicates.Enabled = false;

            float error;
            var perr = float.TryParse(gui_tb_bit_error_rate.Text, NumberStyles.Float,
                             CultureInfo.InvariantCulture.NumberFormat, out error);

            if(!perr)
            {
                error = 0.17f;
                gui_tb_bit_error_rate.Text = "0.17";
            }

            textBox1.Text = error.ToString();

            in_file = selected;
            this.size = int.Parse(gui_tb_size.Value.ToString());

            gui_pb_in_image.ImageLocation = in_file;

            

            var cParams = $"-i ./in -o ./out -d {in_file} -h {hash} -r {this.size} -et {error_type} --get_path";
            var cParams_dup = $"-i ./in -o ./out -d {in_file} -h {hash} -r {this.size} -e {error} -et {error_type}";

            label2.Text = cParams;
            label3.Text = cParams_dup;

            Process process = new Process();
            process.StartInfo.FileName = "./phash.exe";
            process.StartInfo.Arguments = cParams;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.RedirectStandardError = true;
            process.StartInfo.CreateNoWindow = true;
            process.Start();

            string output = process.StandardOutput.ReadToEnd();

            string err = process.StandardError.ReadToEnd();

            process.WaitForExit();

            out_path_file = output;

            
            process.StartInfo.Arguments = cParams_dup;
            process.Start();

            //output = process.StandardOutput.ReadToEnd();

            process.WaitForExit();

            //var duplicates_p = output.Split('|');

            var dup_file_p = Path.ChangeExtension(out_path_file, "dup");

            var duplicates_p = File.ReadAllLines(dup_file_p);

            //string message = "";
            //string title = "dup";

            //foreach(var line in duplicates_p)
            //{
            //    message += line + "\n";
            //}

            //MessageBox.Show(message, title);

            gui_il_duplicates.SuspendLayout();
            gui_il_duplicates.Items.Clear();

            foreach(var path in duplicates_p.Reverse())
            {
                ImageListViewItem item = new ImageListViewItem(path);
                gui_il_duplicates.Items.Add(item);
            }
            gui_il_duplicates.ResumeLayout();


            doUpdate = false;
            gui_lv_in_files.Enabled = true;
            gui_b_find_duplicates.Enabled = true;
        }

        private void gui_cb_hash_SelectedIndexChanged(object sender, EventArgs e)
        {
            hash = gui_cb_hash.SelectedItem.ToString();
            doUpdate = true;
        }
    }
}
