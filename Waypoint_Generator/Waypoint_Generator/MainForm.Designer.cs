namespace Waypoint_Generator
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.waypointControlGroup = new System.Windows.Forms.GroupBox();
            this.waypointRadiusTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.logLabel = new System.Windows.Forms.Label();
            this.logTextBox = new System.Windows.Forms.TextBox();
            this.modeMoveButton = new System.Windows.Forms.Button();
            this.waypointDirectionLabel = new System.Windows.Forms.Label();
            this.modeEditButton = new System.Windows.Forms.Button();
            this.waypointDeleteButton = new System.Windows.Forms.Button();
            this.waypointYLabel = new System.Windows.Forms.Label();
            this.waypointXLabel = new System.Windows.Forms.Label();
            this.waypointXTextBox = new System.Windows.Forms.TextBox();
            this.waypointYTextBox = new System.Windows.Forms.TextBox();
            this.waypointApplyButton = new System.Windows.Forms.Button();
            this.waypointDirectionComboBox = new System.Windows.Forms.ComboBox();
            this.waypointSpeedTextBox = new System.Windows.Forms.TextBox();
            this.waypointSpeedLabel = new System.Windows.Forms.Label();
            this.waypointNumberLabel = new System.Windows.Forms.Label();
            this.waypointNumberTextBox = new System.Windows.Forms.TextBox();
            this.cursorXLabel = new System.Windows.Forms.Label();
            this.cursorYLabel = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fileMenuLoadMap = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.fileMenuLoadWaypoints = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.fileMenuSaveWaypoints = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.fileMenuSettings = new System.Windows.Forms.ToolStripMenuItem();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripAutoConnectCaption = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripAutoConnectStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.map = new System.Windows.Forms.PictureBox();
            this.waypointControlGroup.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.map)).BeginInit();
            this.SuspendLayout();
            // 
            // waypointControlGroup
            // 
            this.waypointControlGroup.Controls.Add(this.waypointRadiusTextBox);
            this.waypointControlGroup.Controls.Add(this.label1);
            this.waypointControlGroup.Controls.Add(this.logLabel);
            this.waypointControlGroup.Controls.Add(this.logTextBox);
            this.waypointControlGroup.Controls.Add(this.modeMoveButton);
            this.waypointControlGroup.Controls.Add(this.waypointDirectionLabel);
            this.waypointControlGroup.Controls.Add(this.modeEditButton);
            this.waypointControlGroup.Controls.Add(this.waypointDeleteButton);
            this.waypointControlGroup.Controls.Add(this.waypointYLabel);
            this.waypointControlGroup.Controls.Add(this.waypointXLabel);
            this.waypointControlGroup.Controls.Add(this.waypointXTextBox);
            this.waypointControlGroup.Controls.Add(this.waypointYTextBox);
            this.waypointControlGroup.Controls.Add(this.waypointApplyButton);
            this.waypointControlGroup.Controls.Add(this.waypointDirectionComboBox);
            this.waypointControlGroup.Controls.Add(this.waypointSpeedTextBox);
            this.waypointControlGroup.Controls.Add(this.waypointSpeedLabel);
            this.waypointControlGroup.Controls.Add(this.waypointNumberLabel);
            this.waypointControlGroup.Controls.Add(this.waypointNumberTextBox);
            this.waypointControlGroup.Location = new System.Drawing.Point(79, 542);
            this.waypointControlGroup.Name = "waypointControlGroup";
            this.waypointControlGroup.Size = new System.Drawing.Size(862, 170);
            this.waypointControlGroup.TabIndex = 1;
            this.waypointControlGroup.TabStop = false;
            this.waypointControlGroup.Text = "Waypoint Control";
            // 
            // waypointRadiusTextBox
            // 
            this.waypointRadiusTextBox.Enabled = false;
            this.waypointRadiusTextBox.Location = new System.Drawing.Point(128, 108);
            this.waypointRadiusTextBox.MaxLength = 4;
            this.waypointRadiusTextBox.Name = "waypointRadiusTextBox";
            this.waypointRadiusTextBox.Size = new System.Drawing.Size(30, 20);
            this.waypointRadiusTextBox.TabIndex = 19;
            this.waypointRadiusTextBox.ModifiedChanged += new System.EventHandler(this.TextBox_ModifiedChanged);
            this.waypointRadiusTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numericTextBox_KeyPress);
            this.waypointRadiusTextBox.Validating += new System.ComponentModel.CancelEventHandler(this.waypointRadiusTextBox_Validating);
            this.waypointRadiusTextBox.Validated += new System.EventHandler(this.TextBox_Validated);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 111);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 13);
            this.label1.TabIndex = 18;
            this.label1.Text = "Waypoint Size (px)";
            // 
            // logLabel
            // 
            this.logLabel.AutoSize = true;
            this.logLabel.Location = new System.Drawing.Point(636, 16);
            this.logLabel.Name = "logLabel";
            this.logLabel.Size = new System.Drawing.Size(28, 13);
            this.logLabel.TabIndex = 16;
            this.logLabel.Text = "Log:";
            // 
            // logTextBox
            // 
            this.logTextBox.Location = new System.Drawing.Point(474, 32);
            this.logTextBox.Multiline = true;
            this.logTextBox.Name = "logTextBox";
            this.logTextBox.ReadOnly = true;
            this.logTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.logTextBox.Size = new System.Drawing.Size(372, 115);
            this.logTextBox.TabIndex = 15;
            // 
            // modeMoveButton
            // 
            this.modeMoveButton.Enabled = false;
            this.modeMoveButton.ForeColor = System.Drawing.Color.Blue;
            this.modeMoveButton.Location = new System.Drawing.Point(363, 53);
            this.modeMoveButton.Name = "modeMoveButton";
            this.modeMoveButton.Size = new System.Drawing.Size(92, 23);
            this.modeMoveButton.TabIndex = 14;
            this.modeMoveButton.Text = "MOVE MODE";
            this.modeMoveButton.UseVisualStyleBackColor = true;
            this.modeMoveButton.Click += new System.EventHandler(this.modeMoveButton_Click);
            // 
            // waypointDirectionLabel
            // 
            this.waypointDirectionLabel.AutoSize = true;
            this.waypointDirectionLabel.Location = new System.Drawing.Point(6, 142);
            this.waypointDirectionLabel.Name = "waypointDirectionLabel";
            this.waypointDirectionLabel.Size = new System.Drawing.Size(109, 13);
            this.waypointDirectionLabel.TabIndex = 5;
            this.waypointDirectionLabel.Text = "Direction to Waypoint";
            // 
            // modeEditButton
            // 
            this.modeEditButton.Enabled = false;
            this.modeEditButton.ForeColor = System.Drawing.Color.Blue;
            this.modeEditButton.Location = new System.Drawing.Point(363, 19);
            this.modeEditButton.Name = "modeEditButton";
            this.modeEditButton.Size = new System.Drawing.Size(92, 23);
            this.modeEditButton.TabIndex = 13;
            this.modeEditButton.Text = "EDIT MODE";
            this.modeEditButton.UseVisualStyleBackColor = true;
            this.modeEditButton.Click += new System.EventHandler(this.modeEditButton_Click);
            // 
            // waypointDeleteButton
            // 
            this.waypointDeleteButton.Enabled = false;
            this.waypointDeleteButton.ForeColor = System.Drawing.Color.Red;
            this.waypointDeleteButton.Location = new System.Drawing.Point(254, 106);
            this.waypointDeleteButton.Name = "waypointDeleteButton";
            this.waypointDeleteButton.Size = new System.Drawing.Size(75, 23);
            this.waypointDeleteButton.TabIndex = 5;
            this.waypointDeleteButton.Text = "Delete Last";
            this.waypointDeleteButton.UseVisualStyleBackColor = true;
            this.waypointDeleteButton.Click += new System.EventHandler(this.waypointDeleteButton_Click);
            // 
            // waypointYLabel
            // 
            this.waypointYLabel.AutoSize = true;
            this.waypointYLabel.Location = new System.Drawing.Point(68, 25);
            this.waypointYLabel.Name = "waypointYLabel";
            this.waypointYLabel.Size = new System.Drawing.Size(12, 13);
            this.waypointYLabel.TabIndex = 12;
            this.waypointYLabel.Text = "y";
            // 
            // waypointXLabel
            // 
            this.waypointXLabel.AutoSize = true;
            this.waypointXLabel.Location = new System.Drawing.Point(12, 25);
            this.waypointXLabel.Name = "waypointXLabel";
            this.waypointXLabel.Size = new System.Drawing.Size(12, 13);
            this.waypointXLabel.TabIndex = 11;
            this.waypointXLabel.Text = "x";
            // 
            // waypointXTextBox
            // 
            this.waypointXTextBox.Location = new System.Drawing.Point(30, 22);
            this.waypointXTextBox.Name = "waypointXTextBox";
            this.waypointXTextBox.ReadOnly = true;
            this.waypointXTextBox.Size = new System.Drawing.Size(29, 20);
            this.waypointXTextBox.TabIndex = 8;
            // 
            // waypointYTextBox
            // 
            this.waypointYTextBox.Location = new System.Drawing.Point(86, 22);
            this.waypointYTextBox.Name = "waypointYTextBox";
            this.waypointYTextBox.ReadOnly = true;
            this.waypointYTextBox.Size = new System.Drawing.Size(29, 20);
            this.waypointYTextBox.TabIndex = 9;
            // 
            // waypointApplyButton
            // 
            this.waypointApplyButton.Enabled = false;
            this.waypointApplyButton.Location = new System.Drawing.Point(254, 139);
            this.waypointApplyButton.Name = "waypointApplyButton";
            this.waypointApplyButton.Size = new System.Drawing.Size(75, 23);
            this.waypointApplyButton.TabIndex = 6;
            this.waypointApplyButton.Text = "Apply";
            this.waypointApplyButton.UseVisualStyleBackColor = true;
            this.waypointApplyButton.Click += new System.EventHandler(this.waypointApplyButton_Click);
            // 
            // waypointDirectionComboBox
            // 
            this.waypointDirectionComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.waypointDirectionComboBox.Enabled = false;
            this.waypointDirectionComboBox.FormattingEnabled = true;
            this.waypointDirectionComboBox.Items.AddRange(new object[] {
            "Forwards",
            "Backwards"});
            this.waypointDirectionComboBox.Location = new System.Drawing.Point(128, 139);
            this.waypointDirectionComboBox.MaxDropDownItems = 2;
            this.waypointDirectionComboBox.Name = "waypointDirectionComboBox";
            this.waypointDirectionComboBox.Size = new System.Drawing.Size(91, 21);
            this.waypointDirectionComboBox.TabIndex = 2;
            this.waypointDirectionComboBox.MouseClick += new System.Windows.Forms.MouseEventHandler(this.waypointDirectionComboBox_MouseClick);
            // 
            // waypointSpeedTextBox
            // 
            this.waypointSpeedTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.waypointSpeedTextBox.Enabled = false;
            this.waypointSpeedTextBox.Location = new System.Drawing.Point(128, 81);
            this.waypointSpeedTextBox.MaxLength = 3;
            this.waypointSpeedTextBox.Name = "waypointSpeedTextBox";
            this.waypointSpeedTextBox.Size = new System.Drawing.Size(30, 20);
            this.waypointSpeedTextBox.TabIndex = 0;
            this.waypointSpeedTextBox.ModifiedChanged += new System.EventHandler(this.TextBox_ModifiedChanged);
            this.waypointSpeedTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numericTextBox_KeyPress);
            this.waypointSpeedTextBox.Validating += new System.ComponentModel.CancelEventHandler(this.waypointSpeedTextBox_Validating);
            this.waypointSpeedTextBox.Validated += new System.EventHandler(this.TextBox_Validated);
            // 
            // waypointSpeedLabel
            // 
            this.waypointSpeedLabel.AutoSize = true;
            this.waypointSpeedLabel.Location = new System.Drawing.Point(6, 81);
            this.waypointSpeedLabel.Name = "waypointSpeedLabel";
            this.waypointSpeedLabel.Size = new System.Drawing.Size(115, 13);
            this.waypointSpeedLabel.TabIndex = 2;
            this.waypointSpeedLabel.Text = "Speed to Waypoint (%)";
            // 
            // waypointNumberLabel
            // 
            this.waypointNumberLabel.AutoSize = true;
            this.waypointNumberLabel.Location = new System.Drawing.Point(6, 53);
            this.waypointNumberLabel.Name = "waypointNumberLabel";
            this.waypointNumberLabel.Size = new System.Drawing.Size(92, 13);
            this.waypointNumberLabel.TabIndex = 1;
            this.waypointNumberLabel.Text = "Waypoint Number";
            // 
            // waypointNumberTextBox
            // 
            this.waypointNumberTextBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.waypointNumberTextBox.Location = new System.Drawing.Point(127, 53);
            this.waypointNumberTextBox.Name = "waypointNumberTextBox";
            this.waypointNumberTextBox.ReadOnly = true;
            this.waypointNumberTextBox.Size = new System.Drawing.Size(31, 20);
            this.waypointNumberTextBox.TabIndex = 7;
            // 
            // cursorXLabel
            // 
            this.cursorXLabel.AutoSize = true;
            this.cursorXLabel.Location = new System.Drawing.Point(455, 520);
            this.cursorXLabel.Name = "cursorXLabel";
            this.cursorXLabel.Size = new System.Drawing.Size(18, 13);
            this.cursorXLabel.TabIndex = 2;
            this.cursorXLabel.Text = "x: ";
            // 
            // cursorYLabel
            // 
            this.cursorYLabel.AutoSize = true;
            this.cursorYLabel.Location = new System.Drawing.Point(498, 520);
            this.cursorYLabel.Name = "cursorYLabel";
            this.cursorYLabel.Size = new System.Drawing.Size(18, 13);
            this.cursorYLabel.TabIndex = 14;
            this.cursorYLabel.Text = "y: ";
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.SystemColors.MenuBar;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1015, 24);
            this.menuStrip1.TabIndex = 15;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileMenuItem
            // 
            this.fileMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileMenuLoadMap,
            this.toolStripSeparator1,
            this.fileMenuLoadWaypoints,
            this.toolStripSeparator2,
            this.fileMenuSaveWaypoints,
            this.toolStripSeparator3,
            this.fileMenuSettings});
            this.fileMenuItem.Name = "fileMenuItem";
            this.fileMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileMenuItem.Text = "File";
            // 
            // fileMenuLoadMap
            // 
            this.fileMenuLoadMap.Image = global::Waypoint_Generator.Properties.Resources.FolderOpen_16x;
            this.fileMenuLoadMap.Name = "fileMenuLoadMap";
            this.fileMenuLoadMap.Size = new System.Drawing.Size(211, 22);
            this.fileMenuLoadMap.Text = "Load Map Image";
            this.fileMenuLoadMap.Click += new System.EventHandler(this.fileMenuLoadMap_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(208, 6);
            // 
            // fileMenuLoadWaypoints
            // 
            this.fileMenuLoadWaypoints.Enabled = false;
            this.fileMenuLoadWaypoints.Image = global::Waypoint_Generator.Properties.Resources.FolderOpen_16x;
            this.fileMenuLoadWaypoints.Name = "fileMenuLoadWaypoints";
            this.fileMenuLoadWaypoints.Size = new System.Drawing.Size(211, 22);
            this.fileMenuLoadWaypoints.Text = "Load Waypoints From File";
            this.fileMenuLoadWaypoints.Click += new System.EventHandler(this.fileMenuLoadWaypoints_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(208, 6);
            // 
            // fileMenuSaveWaypoints
            // 
            this.fileMenuSaveWaypoints.Enabled = false;
            this.fileMenuSaveWaypoints.Image = global::Waypoint_Generator.Properties.Resources.Save_16x;
            this.fileMenuSaveWaypoints.Name = "fileMenuSaveWaypoints";
            this.fileMenuSaveWaypoints.Size = new System.Drawing.Size(211, 22);
            this.fileMenuSaveWaypoints.Text = "Save Waypoints To File";
            this.fileMenuSaveWaypoints.Click += new System.EventHandler(this.fileMenuSaveWaypoints_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(208, 6);
            // 
            // fileMenuSettings
            // 
            this.fileMenuSettings.Image = global::Waypoint_Generator.Properties.Resources.ConnectEnvironment_16x;
            this.fileMenuSettings.Name = "fileMenuSettings";
            this.fileMenuSettings.Size = new System.Drawing.Size(211, 22);
            this.fileMenuSettings.Text = "Settings";
            this.fileMenuSettings.Click += new System.EventHandler(this.fileMenuSettings_Click);
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripAutoConnectCaption,
            this.toolStripAutoConnectStatus});
            this.statusStrip1.Location = new System.Drawing.Point(0, 719);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1015, 22);
            this.statusStrip1.SizingGrip = false;
            this.statusStrip1.TabIndex = 16;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripAutoConnectCaption
            // 
            this.toolStripAutoConnectCaption.Name = "toolStripAutoConnectCaption";
            this.toolStripAutoConnectCaption.Size = new System.Drawing.Size(136, 17);
            this.toolStripAutoConnectCaption.Text = "TP Auto Connect Status:";
            // 
            // toolStripAutoConnectStatus
            // 
            this.toolStripAutoConnectStatus.Name = "toolStripAutoConnectStatus";
            this.toolStripAutoConnectStatus.Size = new System.Drawing.Size(79, 17);
            this.toolStripAutoConnectStatus.Text = "Disconnected";
            // 
            // map
            // 
            this.map.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.map.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.map.Cursor = System.Windows.Forms.Cursors.Cross;
            this.map.InitialImage = null;
            this.map.Location = new System.Drawing.Point(94, 41);
            this.map.Name = "map";
            this.map.Size = new System.Drawing.Size(832, 468);
            this.map.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.map.TabIndex = 0;
            this.map.TabStop = false;
            this.map.SizeChanged += new System.EventHandler(this.map_SizeChanged);
            this.map.Paint += new System.Windows.Forms.PaintEventHandler(this.map_Paint);
            this.map.MouseDown += new System.Windows.Forms.MouseEventHandler(this.map_MouseDown);
            this.map.MouseMove += new System.Windows.Forms.MouseEventHandler(this.map_MouseMove);
            this.map.MouseUp += new System.Windows.Forms.MouseEventHandler(this.map_MouseUp);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1015, 741);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.cursorYLabel);
            this.Controls.Add(this.cursorXLabel);
            this.Controls.Add(this.waypointControlGroup);
            this.Controls.Add(this.map);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Waypoint Generator";
            this.waypointControlGroup.ResumeLayout(false);
            this.waypointControlGroup.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.map)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox map;
        private System.Windows.Forms.GroupBox waypointControlGroup;
        private System.Windows.Forms.Label waypointNumberLabel;
        private System.Windows.Forms.TextBox waypointNumberTextBox;
        private System.Windows.Forms.Label waypointSpeedLabel;
        private System.Windows.Forms.Label waypointDirectionLabel;
        private System.Windows.Forms.ComboBox waypointDirectionComboBox;
        private System.Windows.Forms.TextBox waypointSpeedTextBox;
        private System.Windows.Forms.Button waypointApplyButton;
        private System.Windows.Forms.Button waypointDeleteButton;
        private System.Windows.Forms.Label waypointYLabel;
        private System.Windows.Forms.Label waypointXLabel;
        private System.Windows.Forms.TextBox waypointXTextBox;
        private System.Windows.Forms.TextBox waypointYTextBox;
        private System.Windows.Forms.Label cursorXLabel;
        private System.Windows.Forms.Label cursorYLabel;
        private System.Windows.Forms.Button modeMoveButton;
        private System.Windows.Forms.Button modeEditButton;
        private System.Windows.Forms.TextBox logTextBox;
        private System.Windows.Forms.Label logLabel;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fileMenuLoadMap;
        private System.Windows.Forms.ToolStripMenuItem fileMenuSettings;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem fileMenuLoadWaypoints;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ErrorProvider errorProvider1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripAutoConnectCaption;
        private System.Windows.Forms.ToolStripStatusLabel toolStripAutoConnectStatus;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem fileMenuSaveWaypoints;
        private System.Windows.Forms.TextBox waypointRadiusTextBox;
        private System.Windows.Forms.Label label1;
    }
}

