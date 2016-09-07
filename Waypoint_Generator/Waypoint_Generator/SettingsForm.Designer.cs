namespace Waypoint_Generator
{
    partial class SettingsForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SettingsForm));
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.textBoxIPAddress = new System.Windows.Forms.TextBox();
            this.labelPort = new System.Windows.Forms.Label();
            this.labelIPAddress = new System.Windows.Forms.Label();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.waypointsGroupBox = new System.Windows.Forms.GroupBox();
            this.defaultWaypointDirectionLabel = new System.Windows.Forms.Label();
            this.defaultWaypointDirectionComboBox = new System.Windows.Forms.ComboBox();
            this.defaultSpeedlabel = new System.Windows.Forms.Label();
            this.defaultSpeedTextBox = new System.Windows.Forms.TextBox();
            this.defaultSizelabel = new System.Windows.Forms.Label();
            this.defaultSizeTextBox = new System.Windows.Forms.TextBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.waypointsGroupBox.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.textBoxPort);
            this.tabPage2.Controls.Add(this.textBoxIPAddress);
            this.tabPage2.Controls.Add(this.labelPort);
            this.tabPage2.Controls.Add(this.labelIPAddress);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(203, 186);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Server Settings";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(6, 81);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(57, 20);
            this.textBoxPort.TabIndex = 13;
            this.textBoxPort.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxPort_Validating);
            this.textBoxPort.Validated += new System.EventHandler(this.textBoxPort_Validated);
            // 
            // textBoxIPAddress
            // 
            this.textBoxIPAddress.Location = new System.Drawing.Point(6, 33);
            this.textBoxIPAddress.Name = "textBoxIPAddress";
            this.textBoxIPAddress.Size = new System.Drawing.Size(106, 20);
            this.textBoxIPAddress.TabIndex = 12;
            this.textBoxIPAddress.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxIPAddress_Validating);
            this.textBoxIPAddress.Validated += new System.EventHandler(this.textBoxIPAddress_Validated);
            // 
            // labelPort
            // 
            this.labelPort.AutoSize = true;
            this.labelPort.Location = new System.Drawing.Point(6, 65);
            this.labelPort.Name = "labelPort";
            this.labelPort.Size = new System.Drawing.Size(63, 13);
            this.labelPort.TabIndex = 11;
            this.labelPort.Text = "Server Port:";
            // 
            // labelIPAddress
            // 
            this.labelIPAddress.AutoSize = true;
            this.labelIPAddress.Location = new System.Drawing.Point(6, 17);
            this.labelIPAddress.Name = "labelIPAddress";
            this.labelIPAddress.Size = new System.Drawing.Size(95, 13);
            this.labelIPAddress.TabIndex = 10;
            this.labelIPAddress.Text = "Server IP Address:";
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.waypointsGroupBox);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(203, 186);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "General";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // waypointsGroupBox
            // 
            this.waypointsGroupBox.Controls.Add(this.defaultWaypointDirectionLabel);
            this.waypointsGroupBox.Controls.Add(this.defaultWaypointDirectionComboBox);
            this.waypointsGroupBox.Controls.Add(this.defaultSpeedlabel);
            this.waypointsGroupBox.Controls.Add(this.defaultSpeedTextBox);
            this.waypointsGroupBox.Controls.Add(this.defaultSizelabel);
            this.waypointsGroupBox.Controls.Add(this.defaultSizeTextBox);
            this.waypointsGroupBox.Location = new System.Drawing.Point(7, 17);
            this.waypointsGroupBox.Name = "waypointsGroupBox";
            this.waypointsGroupBox.Size = new System.Drawing.Size(179, 149);
            this.waypointsGroupBox.TabIndex = 0;
            this.waypointsGroupBox.TabStop = false;
            this.waypointsGroupBox.Text = "Waypoints";
            // 
            // defaultWaypointDirectionLabel
            // 
            this.defaultWaypointDirectionLabel.AutoSize = true;
            this.defaultWaypointDirectionLabel.Location = new System.Drawing.Point(6, 103);
            this.defaultWaypointDirectionLabel.Name = "defaultWaypointDirectionLabel";
            this.defaultWaypointDirectionLabel.Size = new System.Drawing.Size(149, 13);
            this.defaultWaypointDirectionLabel.TabIndex = 19;
            this.defaultWaypointDirectionLabel.Text = "Default Direction to Waypoint:";
            // 
            // defaultWaypointDirectionComboBox
            // 
            this.defaultWaypointDirectionComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.defaultWaypointDirectionComboBox.FormattingEnabled = true;
            this.defaultWaypointDirectionComboBox.Items.AddRange(new object[] {
            "Forwards",
            "Backwards"});
            this.defaultWaypointDirectionComboBox.Location = new System.Drawing.Point(9, 122);
            this.defaultWaypointDirectionComboBox.MaxDropDownItems = 2;
            this.defaultWaypointDirectionComboBox.Name = "defaultWaypointDirectionComboBox";
            this.defaultWaypointDirectionComboBox.Size = new System.Drawing.Size(91, 21);
            this.defaultWaypointDirectionComboBox.TabIndex = 18;
            // 
            // defaultSpeedlabel
            // 
            this.defaultSpeedlabel.AutoSize = true;
            this.defaultSpeedlabel.Location = new System.Drawing.Point(6, 58);
            this.defaultSpeedlabel.Name = "defaultSpeedlabel";
            this.defaultSpeedlabel.Size = new System.Drawing.Size(159, 13);
            this.defaultSpeedlabel.TabIndex = 17;
            this.defaultSpeedlabel.Text = "Default Speed To Waypoint (%):";
            // 
            // defaultSpeedTextBox
            // 
            this.defaultSpeedTextBox.Location = new System.Drawing.Point(9, 77);
            this.defaultSpeedTextBox.Name = "defaultSpeedTextBox";
            this.defaultSpeedTextBox.Size = new System.Drawing.Size(57, 20);
            this.defaultSpeedTextBox.TabIndex = 16;
            this.defaultSpeedTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numericTextBox_KeyPress);
            this.defaultSpeedTextBox.Validating += new System.ComponentModel.CancelEventHandler(this.defaultSpeedTextBox_Validating);
            this.defaultSpeedTextBox.Validated += new System.EventHandler(this.defaultSpeedTextBox_Validated);
            // 
            // defaultSizelabel
            // 
            this.defaultSizelabel.AutoSize = true;
            this.defaultSizelabel.Location = new System.Drawing.Point(6, 16);
            this.defaultSizelabel.Name = "defaultSizelabel";
            this.defaultSizelabel.Size = new System.Drawing.Size(87, 13);
            this.defaultSizelabel.TabIndex = 15;
            this.defaultSizelabel.Text = "Default Size (px):";
            // 
            // defaultSizeTextBox
            // 
            this.defaultSizeTextBox.Location = new System.Drawing.Point(9, 35);
            this.defaultSizeTextBox.Name = "defaultSizeTextBox";
            this.defaultSizeTextBox.Size = new System.Drawing.Size(57, 20);
            this.defaultSizeTextBox.TabIndex = 14;
            this.defaultSizeTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numericTextBox_KeyPress);
            this.defaultSizeTextBox.Validating += new System.ComponentModel.CancelEventHandler(this.defaultSizeTextBox_Validating);
            this.defaultSizeTextBox.Validated += new System.EventHandler(this.defaultSizeTextBox_Validated);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(211, 212);
            this.tabControl1.TabIndex = 6;
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(144, 236);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 19;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(63, 236);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 18;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(234, 272);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SettingsForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Settings";
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            this.waypointsGroupBox.ResumeLayout(false);
            this.waypointsGroupBox.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ErrorProvider errorProvider1;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.TextBox textBoxIPAddress;
        private System.Windows.Forms.Label labelPort;
        private System.Windows.Forms.Label labelIPAddress;
        private System.Windows.Forms.GroupBox waypointsGroupBox;
        private System.Windows.Forms.Label defaultSizelabel;
        private System.Windows.Forms.TextBox defaultSizeTextBox;
        private System.Windows.Forms.Label defaultSpeedlabel;
        private System.Windows.Forms.TextBox defaultSpeedTextBox;
        private System.Windows.Forms.Label defaultWaypointDirectionLabel;
        private System.Windows.Forms.ComboBox defaultWaypointDirectionComboBox;
    }
}