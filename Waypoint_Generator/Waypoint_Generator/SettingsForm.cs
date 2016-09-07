using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Text.RegularExpressions;

namespace Waypoint_Generator
{
    public partial class SettingsForm : Form
    {
        public SettingsForm()
        {
            InitializeComponent();
            textBoxIPAddress.Text = Properties.Settings.Default.server_ip;
            textBoxPort.Text = Properties.Settings.Default.server_port.ToString();
            defaultSizeTextBox.Text = Properties.Settings.Default.defaultWaypointSize.ToString();
            defaultSpeedTextBox.Text = Properties.Settings.Default.defaultWaypointSpeed.ToString();
            defaultWaypointDirectionComboBox.SelectedItem = Properties.Settings.Default.defaultWaypointDirection;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            String ip_addr = textBoxIPAddress.Text;
            String port = textBoxPort.Text;
            String size = defaultSizeTextBox.Text;
            String speed = defaultSpeedTextBox.Text;
            String direction = defaultWaypointDirectionComboBox.SelectedItem.ToString();

            //Note: These are guaranteed to be correct string formats as Textbox entries are validated before OK can be clicked
            Properties.Settings.Default.server_ip = ip_addr;
            Properties.Settings.Default.server_port = Convert.ToInt32(port);
            Properties.Settings.Default.defaultWaypointSize = Convert.ToInt32(size);
            Properties.Settings.Default.defaultWaypointSpeed = Convert.ToInt32(speed);
            Properties.Settings.Default.defaultWaypointDirection = direction;

            //Persist this users settings on next launch
            Properties.Settings.Default.Save();

            DialogResult = DialogResult.OK;

            //Close form
            Close();
        }

        private void numericTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            //Attach any TextBox's KeyPress event where only numeric characters are valid

            //Disallow any character that is not a digit or control character (e.g. backspace)
            if (!char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar))
            {
                //Mark KeyPress event as being handled to stop it being handled by control itself
                //(prevents character being added to control)
                e.Handled = true;
            }
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;

            //Close form
            Close();
        }

        #region Control Validation
        private bool isValidIPAddress(String strIP, out string err_str)
        {
            if (!String.IsNullOrEmpty(strIP))
            {
                //  Split string by ".", check that array length is 4
                string[] arrOctets = strIP.Split('.');
                if (arrOctets.Length != 4)
                {
                    err_str = "Invalid IPv4 format!";
                    return false;
                }
                //Check each octet substring checking that parses to byte (0-255)
                byte obyte = 0;
                foreach (string strOctet in arrOctets)
                {
                    if (!byte.TryParse(strOctet, out obyte))
                    {
                        err_str = "Invalid IPv4 format!";
                        return false;
                    }
                }

                err_str = "";
                return true;
            }
            err_str = "IPv4 address must be entered!";
            return false;
        }

        private bool isValidPort(String port, out string err_str)
        {
            if (!String.IsNullOrEmpty(port))
            {
                Regex numericPort = new Regex(@"^[0-9]+$", RegexOptions.Compiled | RegexOptions.IgnoreCase);

                if(numericPort.IsMatch(port))
                {
                    if (Convert.ToInt32(port) < 65536)
                    {
                        err_str = "";
                        return true;
                    }
                    else
                    { 
                        err_str = "Port must be an integer in range 0-65536!";
                        return false;
                    }
                }
                else
                {
                    err_str = "Port must be an integer in range 0-65536!";
                    return false;
                }
            }
            err_str = "Port number must be entered!";
            return false;
        }

        private bool isValidSize(String size, out string err_str)
        {
            if (!String.IsNullOrEmpty(size))
            {
                Regex numericPort = new Regex(@"^[0-9]+$", RegexOptions.Compiled | RegexOptions.IgnoreCase);

                if (numericPort.IsMatch(size))
                {
                    Int32 _size = Convert.ToInt32(size);
                    if (_size >0 && _size <= 1000)
                    {
                        err_str = "";
                        return true;
                    }
                    else
                    {
                        err_str = "Size must be an integer in range 1-1000!";
                        return false;
                    }
                }
                else
                {
                    err_str = "Size must be an integer in range 1-1000!";
                    return false;
                }
            }
            err_str = "Size must be entered!";
            return false;
        }

        private bool isValidSpeed(String speed, out string error_str)
        {
            int i = 0;

            if (speed.Length == 0)
            {
                error_str = "You must enter an integer speed in range 1-100!";
                return false;
            }

            if (!int.TryParse(speed, out i))
            {
                error_str = "Speed must be a integer number in range 1-100!";
                return false;
            }

            //If here, speed is an integer, check its range
            if (i < 1 || i > 100)
            {
                error_str = "Speed must be a integer number in range 1-100!";
                return false;
            }

            //If here, speed is valid
            error_str = "";
            return true;
        }

        private void textBoxIPAddress_Validating(object sender, CancelEventArgs e)
        {
            string err_str;

            TextBox textBox = (TextBox)sender;

            if (!isValidIPAddress(textBox.Text, out err_str))
            {
                errorProvider1.SetError(textBox, err_str);
                textBox.BackColor = Color.Red;
                e.Cancel = true;
            }
        }

        private void textBoxIPAddress_Validated(object sender, EventArgs e)
        {
            TextBox textBox = (TextBox)sender;

            //Successfully passed validation, clear error
            errorProvider1.SetError(textBox, "");
            textBox.BackColor = Color.White;
        }

        private void textBoxPort_Validating(object sender, CancelEventArgs e)
        {
            string err_str;
            TextBox textBox = (TextBox)sender;

            if (!isValidPort(textBox.Text, out err_str))
            {
                errorProvider1.SetError(textBox, err_str);
                textBox.BackColor = Color.Red;
                e.Cancel = true;
            }
        }

        private void textBoxPort_Validated(object sender, EventArgs e)
        {
            TextBox textBox = (TextBox)sender;

            //Successfully passed validation, clear error
            errorProvider1.SetError(textBox, "");
            textBox.BackColor = Color.White;
        }

        private void defaultSizeTextBox_Validating(object sender, CancelEventArgs e)
        {
            string err_str;
            TextBox textBox = (TextBox)sender;

            if (!isValidSize(textBox.Text, out err_str))
            {
                errorProvider1.SetError(textBox, err_str);
                textBox.BackColor = Color.Red;
                e.Cancel = true;
            }
        }

        private void defaultSizeTextBox_Validated(object sender, EventArgs e)
        {
            TextBox textBox = (TextBox)sender;

            //Successfully passed validation, clear error
            errorProvider1.SetError(textBox, "");
            textBox.BackColor = Color.White;
        }

        private void defaultSpeedTextBox_Validating(object sender, CancelEventArgs e)
        {
            string error_str;
            TextBox textBox = (TextBox)sender;

            if (!isValidSpeed(textBox.Text, out error_str))
            {
                e.Cancel = true;
                //Select the textbox content to be changed
                textBox.Select(0, textBox.Text.Length);
                //Change background of textbox to red to highlight error
                textBox.BackColor = Color.Red;

                //Display error next to control using errorProvider1
                errorProvider1.SetError(textBox, error_str);
            }
        }

        private void defaultSpeedTextBox_Validated(object sender, EventArgs e)
        {
            TextBox textBox = (TextBox)sender;

            //Successfully passed validation, clear error
            errorProvider1.SetError(textBox, "");
            textBox.BackColor = Color.White;
        }
        #endregion

        
    }
}
