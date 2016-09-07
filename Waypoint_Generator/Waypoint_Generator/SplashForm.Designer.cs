namespace Waypoint_Generator
{
    partial class SplashForm
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
            this.labelCopyrightInfo = new System.Windows.Forms.Label();
            this.labelVersion = new System.Windows.Forms.Label();
            this.labelYear = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // labelCopyrightInfo
            // 
            this.labelCopyrightInfo.AutoSize = true;
            this.labelCopyrightInfo.BackColor = System.Drawing.Color.Transparent;
            this.labelCopyrightInfo.Font = new System.Drawing.Font("Calibri", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelCopyrightInfo.ForeColor = System.Drawing.Color.White;
            this.labelCopyrightInfo.Location = new System.Drawing.Point(323, 278);
            this.labelCopyrightInfo.Name = "labelCopyrightInfo";
            this.labelCopyrightInfo.Size = new System.Drawing.Size(74, 14);
            this.labelCopyrightInfo.TabIndex = 0;
            this.labelCopyrightInfo.Text = "© Paul Harris";
            // 
            // labelVersion
            // 
            this.labelVersion.AutoSize = true;
            this.labelVersion.BackColor = System.Drawing.Color.Transparent;
            this.labelVersion.Font = new System.Drawing.Font("Calibri", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelVersion.ForeColor = System.Drawing.Color.White;
            this.labelVersion.Location = new System.Drawing.Point(191, 99);
            this.labelVersion.Name = "labelVersion";
            this.labelVersion.Size = new System.Drawing.Size(86, 23);
            this.labelVersion.TabIndex = 1;
            this.labelVersion.Text = "<Version>";
            // 
            // labelYear
            // 
            this.labelYear.AutoSize = true;
            this.labelYear.BackColor = System.Drawing.Color.Transparent;
            this.labelYear.Font = new System.Drawing.Font("Calibri", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelYear.ForeColor = System.Drawing.Color.White;
            this.labelYear.Location = new System.Drawing.Point(394, 278);
            this.labelYear.Name = "labelYear";
            this.labelYear.Size = new System.Drawing.Size(40, 14);
            this.labelYear.TabIndex = 2;
            this.labelYear.Text = "<Year>";
            // 
            // SplashForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.BackgroundImage = global::Waypoint_Generator.Properties.Resources.splashscreen2;
            this.ClientSize = new System.Drawing.Size(440, 300);
            this.Controls.Add(this.labelYear);
            this.Controls.Add(this.labelVersion);
            this.Controls.Add(this.labelCopyrightInfo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "SplashForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SplashForm";
            this.TransparencyKey = System.Drawing.Color.Lime;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelCopyrightInfo;
        private System.Windows.Forms.Label labelVersion;
        private System.Windows.Forms.Label labelYear;
    }
}