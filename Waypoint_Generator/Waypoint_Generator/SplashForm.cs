using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Waypoint_Generator
{
    public partial class SplashForm : Form
    {
        public SplashForm(Version version, String year)
        {
            InitializeComponent();

            labelVersion.Text = "v" + version.ToString();
            labelYear.Text = year;
        }
    }
}
