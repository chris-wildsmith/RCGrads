using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.IO;
using System.Reflection;

namespace Waypoint_Generator
{
    public partial class MainForm : Form
    {

        #region Constructor
        //Form Constructor
        public MainForm()
        {

            #region Run Splashscreen
            //Start up thread for splashscreen form to run in
            Thread splashThread = new Thread(new ThreadStart(splashScreen));
            splashThread.Start();
            //Make the current thread (running application) sleep so as to not continue constructing and displaying main form
            Thread.Sleep(Properties.Settings.Default.splashScreenDelay);
            //Kill splashscreen thread and splashscreen form it was running
            splashThread.Abort();
            #endregion

            #region Continue loading main form
            //Initialise main form
            InitializeComponent();
            InitializeMap();
            #endregion
        }
        #endregion

        #region Private Variables and objects
        Waypoints waypoints;

        //State variables
        bool editInProgress;
        bool mouse_held;

        //Sizes for picture box depending on chosen aspect ratio
        const int width_16_9 = 832;
        const int height_16_9 = 468;
        const int width_4_3 = 600;
        const int height_4_3 = 450;

        //4:3 and 16:9 aspect ratio constants
        const double aspect_16_9 = 16.0 / 9;
        const double aspect_4_3 = 4.0 / 3;

        //How much smaller map is displayed compared to source image
        double scale_factor; //Will auto-update when image loaded

        #endregion

        #region Private Enums
        enum eMode { Edit, Move };
        eMode mode;
        enum eAspectRatio {sixteenNine, fourThree};
        eAspectRatio aspectRatio;
        #endregion

        #region Private Methods

        //Starts up splashscreen in current thread
        private void splashScreen()
        {
            Version version = Assembly.GetEntryAssembly().GetName().Version;
            
            //Start a message loop in current thread for a new SplashForm and display form
            Application.Run(new SplashForm(version, "2016"));
        }

        //Initialises state variables for form
        private void InitializeMap()
        {
            this.waypoints = new Waypoints(this.logTextBox);
            this.editInProgress = false;
            this.mouse_held = false;
            this.editMode();//Initialise in edit mode

            //Default to 16:9 aspect ratio to start
            this.changeMapAspectRatio(eAspectRatio.sixteenNine);

            //Subscribe to events
            this.waypoints.waypointsEmpty += new System.EventHandler(waypointsEmpty);
            this.waypoints.waypointAdded += new System.EventHandler(waypointAdded);
        }

        #region Form Controls

        private void enableControls()
        {
            this.waypointSpeedTextBox.Enabled = true;
            this.waypointRadiusTextBox.Enabled = true;
            this.waypointDirectionComboBox.Enabled = true;
        }

        private void disableControls()
        {
            this.waypointSpeedTextBox.Enabled = false;
            this.waypointRadiusTextBox.Enabled = false;
            this.waypointDirectionComboBox.Enabled = false;
        }

        private void enableEdit()
        {
            this.modeEditButton.Enabled = true;
        }

        private void disableEdit()
        {
            this.modeEditButton.Enabled = false;
        }

        private void enableMove()
        {
            this.modeMoveButton.Enabled = true;
        }

        private void disableMove()
        {
            this.modeMoveButton.Enabled = false;
        }

        private void enableApply()
        {
            this.waypointApplyButton.Enabled = true;
        }

        private void disableApply()
        {
            this.waypointApplyButton.Enabled = false;
        }

        private void enableDelete()
        {
            this.waypointDeleteButton.Enabled = true;
        }

        private void disableDelete()
        {
            this.waypointDeleteButton.Enabled = false;
        }

        private void enableWriteFile()
        {
            this.fileMenuSaveWaypoints.Enabled = true;
        }

        private void disableWriteFile()
        {
            this.fileMenuSaveWaypoints.Enabled = false;
        }

        private void enableLoadFile()
        {
            this.fileMenuLoadWaypoints.Enabled = true;
        }

        private void disableLoadFile()
        {
            this.fileMenuLoadWaypoints.Enabled = false;
        }

        private void clearControls()
        {
            this.waypointNumberTextBox.Text = "";
            this.waypointXTextBox.Text = "";
            this.waypointYTextBox.Text = "";
            this.waypointSpeedTextBox.Text = "";
            this.waypointRadiusTextBox.Text = "";
            this.waypointDirectionComboBox.SelectedIndex = -1;
        }

        //Changes aspect ratio of map imagebox
        private void changeMapAspectRatio(eAspectRatio aspect_ratio)
        {
            if (aspect_ratio == eAspectRatio.sixteenNine)
            {
                //Update map size and location
                this.map.Width = width_16_9;
                this.map.Height = height_16_9;

                //Update state variable
                this.aspectRatio = eAspectRatio.sixteenNine;

                this.writeLogLine("Map aspect ratio updated to 16:9.");
            }

            if (aspect_ratio == eAspectRatio.fourThree)
            {
                //Update map size
                this.map.Width = width_4_3;
                this.map.Height = height_4_3;

                //Update state variable
                this.aspectRatio = eAspectRatio.fourThree;

                this.writeLogLine("Map aspect ratio updated to 4:3.");
            }

        }

        #endregion

        #region Mode Control
        private void editMode()
        {
            this.disableEdit();

            //Enable move mode if waypoints to move
            if (waypoints.Count > 0)
            {
                this.enableMove();
            }

            //Clear active selection
            this.clearSelection();

            //Enable delete button if at least one waypoint
            if (this.waypoints.Count > 0)
            {
                this.enableDelete();
            }
            //Set mode to Edit
            this.mode = eMode.Edit;

        }

        private void moveMode()
        {
            this.enableEdit();

            this.disableMove();

            //Clear any currently active edit that has not been applied
            this.editInProgress = false;

            //Clear active selection
            this.clearSelection();

            //Disable controls
            this.disableControls();

            //Disable apply button
            this.disableApply();

            //Disable delete button
            this.disableDelete();

            //Set mode to Move
            this.mode = eMode.Move;
        }
        #endregion

        #region Update controls from waypoint
        private void updateControls(int waypoint_number, int x, int y, int waypoint_speed, eDirection direction, int waypoint_size)
        {
            this.waypointNumberTextBox.Text = waypoint_number.ToString();
            this.waypointXTextBox.Text = x.ToString();
            this.waypointYTextBox.Text = y.ToString();
            this.waypointSpeedTextBox.Text = waypoint_speed.ToString();
            this.waypointDirectionComboBox.SelectedIndex = (int)direction;
            this.waypointRadiusTextBox.Text = waypoint_size.ToString();
        }

        private void updateControls(int waypoint_number, Waypoint wp)
        {
            this.waypointNumberTextBox.Text = waypoint_number.ToString();
            this.waypointXTextBox.Text = wp.x.ToString();
            this.waypointYTextBox.Text = wp.y.ToString();
            this.waypointSpeedTextBox.Text = wp.speed.ToString();
            this.waypointDirectionComboBox.SelectedIndex = (int)wp.direction;
            this.waypointRadiusTextBox.Text = wp.size.ToString();
        }
        #endregion

        #region Update waypoint from controls
        private void updateWpFromControls() //Update waypoint number, speed and direction from controls
        {
            //Get and convert waypoint information from controls to be updated
            int wp_idx = Convert.ToInt32(this.waypointNumberTextBox.Text);
            int speed = Convert.ToInt32(this.waypointSpeedTextBox.Text);
            int size = Convert.ToInt32(this.waypointRadiusTextBox.Text);

            eDirection direction;

            if (this.waypointDirectionComboBox.SelectedIndex == 0)
            {
                direction = eDirection.Forwards;
            }
            else
            {
                direction = eDirection.Backwards;
            }

            this.waypoints.updateSpeed(wp_idx, speed);
            this.waypoints.updateDirection(wp_idx, direction);
            this.waypoints.updateSize(wp_idx, size);

        }
        #endregion

        #region Waypoint Selection
        private void selectWaypoint(int selected_idx)
        {
            //Select waypoint in list
            waypoints.selectWaypoint(selected_idx);

            //Redraw map to show selection
            this.map.Invalidate();
        }

        private void clearSelection()
        {
            this.clearControls();
            this.disableControls();

            //Deselect waypoint if selected
            if (this.waypoints.isSelected)
            {
                this.waypoints.deselectAll();
                this.map.Invalidate();
            }
        }

        #endregion

        private void resetAll()
        {
            //Remove all waypoints from list
            this.waypoints.removeAll();
            //Clear screen
            this.map.Invalidate();
            //Disable/clear controls
            this.clearControls();
            this.disableControls();
            this.disableApply();
            this.disableDelete();

            //Put into Edit mode
            this.editMode();
        }

        private void writeLogLine(String log_string)
        {
            this.logTextBox.AppendText(log_string + Environment.NewLine);
        }

        #endregion
        
        #region Form EventHandlers

        private void modeEditButton_Click(object sender, EventArgs e)
        {
            this.editMode();
        }

        private void modeMoveButton_Click(object sender, EventArgs e)
        {
            this.moveMode();
        }

        private void waypointApplyButton_Click(object sender, EventArgs e)
        {
            if (this.mode == eMode.Edit && this.waypoints.isSelected)
            {
                //Update the waypoint from the user control information
                this.updateWpFromControls();

                //Disable apply button
                this.disableApply();

                //Clear active selection
                this.clearSelection();

                //Finished editing waypoint
                this.editInProgress = false; 
            }
        }

        private void waypointDeleteButton_Click(object sender, EventArgs e)
        {
            if (this.mode == eMode.Edit)
            {
                //Cancel any edit that is in progress
                this.editInProgress = false;
                
                //If there are waypoints to delete, remove the last waypoint in list and redraw
                if (this.waypoints.Count > 0)
                {
                    this.waypoints.removeLastWp();
                    this.map.Invalidate();

                    //Deselect any selected waypoints
                    this.clearSelection();

                    //Disable controls
                    this.disableControls();
                }
            }
        }

        private void TextBox_ModifiedChanged(object sender, EventArgs e)
        {

            if (this.mode == eMode.Edit && this.waypoints.isSelected)
            {
                //Enable apply button
                this.enableApply();

                //We are now editing a waypoint
                this.editInProgress = true;
            }

            TextBox textBox = (TextBox)sender;

            //Reset the modified flag to allow ModifiedChanged to be retriggered.
            textBox.Modified = false;
        }

        private void waypointDirectionComboBox_MouseClick(object sender, EventArgs e)
        {
            if (this.mode == eMode.Edit && this.waypoints.isSelected)
            {
                //Enable apply button
                this.enableApply();

                //We are now editing a waypoint
                this.editInProgress = true;
            }
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

        private void map_MouseDown(object sender, MouseEventArgs e)
        {
            //If left click, attempt to find closest existing waypoint and display its information
            //If right click, create waypoint

            if (!editInProgress) //Only allow selection/addition of waypoints when edit not in progress
            {
                #region Left Click: Select Waypoint
                if (e.Button == MouseButtons.Left)//Left click to select waypoint
                {
                    mouse_held = true; //User is holding left button down

                    //Find the closest waypoint (if any) within 8px threhold to mouse click
                    int selected_idx = waypoints.findClosest(e.Location, 8);

                    //If closest waypoint found within threshold, select it
                    if (selected_idx >= 0)
                    {
                        this.selectWaypoint(selected_idx);

                        //Update the controls with the selected waypoint info
                        Waypoint wp = waypoints.getWaypoint(selected_idx);
                        updateControls(selected_idx, wp);

                        if (this.mode == eMode.Edit)
                        {
                            //Enable controls for editing selected waypoint.
                            this.enableControls();
                        }
                    }
                    else //User not clicked on/near a waypoint
                    {
                        //Deselect any currently selected waypoint
                        this.clearSelection();
                    }

                }
                #endregion

                #region Right Click: Add Waypoint
                else if (e.Button == MouseButtons.Right)//Right click to add waypoint
                {
                    if (this.mode == eMode.Edit) //Add a waypoint only if in edit mode
                    {
                        #region Extra waypoint default info from user settings
                        int defaultSpeed = Properties.Settings.Default.defaultWaypointSpeed;
                        int defaultSize = Properties.Settings.Default.defaultWaypointSize;
                        string defaultDirStr = Properties.Settings.Default.defaultWaypointDirection;
                        eDirection defaultDir;

                        if (defaultDirStr == "Backwards")
                        {
                            defaultDir = eDirection.Backwards;
                        }
                        else
                        {
                            defaultDir = eDirection.Forwards;
                        }
                        #endregion

                        //Create new waypoint with location of mouse down and default information
                        Waypoint wp = new Waypoint(e.X, e.Y, defaultSpeed, defaultDir, defaultSize);

                        //Add waypoint to list
                        waypoints.addWp(wp);

                        //Update controls with newly added waypoint info
                        this.updateControls(waypoints.Count - 1, wp);

                        //Select newly added waypoint
                        this.selectWaypoint(waypoints.Count - 1);
                    }
                }
                #endregion
            }


        }

        private void map_MouseUp(object sender, MouseEventArgs e)
        {

            if (e.Button == MouseButtons.Left)//If left button released
            {
                this.mouse_held = false;
            }
        }

        private void map_MouseMove(object sender, MouseEventArgs e)
        {

            //Update cursor location boxes
            this.cursorXLabel.Text = "X: " + Convert.ToString(e.X);
            this.cursorYLabel.Text = "Y: " + Convert.ToString(e.Y);

            #region Move waypoint
            if (this.mode == eMode.Move && this.mouse_held)//If we are in move mode and the mouse is held down
            {

                if (waypoints.isSelected)//If there is a selected waypoint
                {
                    int x = e.X;
                    int y = e.Y;

                    //Ensure moving of waypoint stays within map bounds
                    if (x < 0) { x = 0; }
                    if (x > this.map.Size.Width) { x = map.Size.Width; }
                    if (y < 0) { y = 0; }
                    if (y > this.map.Size.Height) { y = map.Size.Height; }

                    waypoints.updateLocation(waypoints.selected_idx, x, y);

                    Waypoint wp = waypoints.getWaypoint(waypoints.selected_idx);
                    this.updateControls(waypoints.selected_idx, wp);

                    //Redraw waypoints
                    this.map.Invalidate();
                }
            }
            #endregion

        }

        private void map_Paint(object sender, PaintEventArgs e)
        {
            // Create a local version of the graphics object for the map PictureBox.
            Graphics g = e.Graphics;

            //Waypoint centre square width
            float wp_width = 5;

            //Brushes for waypoint squares
            SolidBrush unselected_brush = new SolidBrush(Color.Red);
            SolidBrush selected_brush = new SolidBrush(Color.Yellow);

            //Brush for waypoint size bounding squares
            SolidBrush waypoint_bounding_brush = new SolidBrush(Color.Blue);

            //Pens for waypoint lines
            Pen forwards_pen = new Pen(Color.Green, 2);
            Pen backwards_pen = new Pen(Color.Red, 2);

            //Get readonly copy of waypoints list
            IReadOnlyCollection<Waypoint> wps = waypoints.waypoints;
            for (int i = 0; i < wps.Count(); i++)
            {
                Waypoint wp = wps.ElementAt(i);

                //Draw the waypoint bounding box
                //N.B. A waypoint is treated as a square in TP s/w and its size is its "radius"
                g.FillRectangle(waypoint_bounding_brush, (wp.x - wp.size), (wp.y - wp.size), wp.size*2, wp.size*2);
               
                //Draw the line to the previous waypoint
                //Note: Direction stored in waypoint is direction to travel to that waypoint
                if (i > 0)
                {
                    Waypoint wp_prev = wps.ElementAt(i - 1);
                    if (wp.direction == eDirection.Forwards)
                    {
                        g.DrawLine(forwards_pen, wp_prev.x, wp_prev.y, wp.x, wp.y);
                    }
                    else
                    {
                        g.DrawLine(backwards_pen, wp_prev.x, wp_prev.y, wp.x, wp.y);
                    }
                }

                //Draw the waypoint centre rectangle
                if (wp.selected)
                {
                    g.FillRectangle(selected_brush, (wp.x - (wp_width / 2)), (wp.y - (wp_width / 2)), wp_width, wp_width);
                }
                else
                {
                    g.FillRectangle(unselected_brush, (wp.x - (wp_width / 2)), (wp.y - (wp_width / 2)), wp_width, wp_width);
                }
            }

        }

        private void map_SizeChanged(object sender, EventArgs e)
        {
            //When map is resized due to aspect ratio change, automatically re-centre it
            //between controls group box and top

            //Calculate centre points of form + control
            int map_x_centre = Convert.ToInt32(this.map.Width/2.0);
            int map_y_centre = Convert.ToInt32(this.map.Height/2.0);

            int form_x_centre = Convert.ToInt32(this.Width/2.0);

            Point point = this.waypointControlGroup.Location;

            int form_y_centre = Convert.ToInt32(point.Y/2.0);

            int map_x = form_x_centre - map_x_centre;
            int map_y = form_y_centre - map_y_centre;

            //Update control top-left point location
            this.map.Location = new Point(map_x, map_y);

        }

        private void waypointsEmpty(object sender, EventArgs e)
        {
            //If there are now no more waypoints remaining, disable delete, move and write file buttons
            this.disableDelete();
            this.disableMove();
            this.disableControls();
            this.disableWriteFile();
        }

        private void waypointAdded(object sender, EventArgs e)
        {
            //Enable controls that were disabled previously when no more waypoints remained
            this.enableDelete();
            this.enableMove();
            this.enableControls();
            //Only enable write file if we have a map image loaded i.e. a non-zero scale factor calculated to allow writing of waypoints file
            if (map.Image != null)
            {
                this.enableWriteFile();
            }
        }

        #region Menubar callbacks
        private void fileMenuLoadMap_Click(object sender, EventArgs e)
        {
            
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Filter = "Image Files(*.BMP; *.JPG; *.GIF)| *.BMP; *.JPG; *.GIF | All files(*.*) | *.*";
            fileDialog.RestoreDirectory = false;

            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                String filename = fileDialog.FileName;
                Image image = null;

                try
                {
                    image = Image.FromFile(filename);
                }
                catch
                {
                    this.writeLogLine("Error: Could not load \"" + filename + "\" ! Check it exists and is a valid image format.");
                }
                
                //Calculate aspect ratio of loaded image
                double aspect_ratio_image = Convert.ToDouble(image.Width) / image.Height;

                //Check if aspect ratio of loaded image is incompatible
                if(aspect_ratio_image != aspect_4_3 && aspect_ratio_image != aspect_16_9)
                {
                    this.writeLogLine("Error: Loaded image aspect must be 4:3 or 16:9!");
                    return;
                }

                //Calculate current aspect ratio of map picture box
                double aspect_ratio_map = Convert.ToDouble(this.map.Width) / this.map.Height;

                //We must ensure the aspect ratio of the image trying to be loaded
                //is the same as the map picture box's otherwise image will be distorted
                //since map picture box shrinks image to fit.  This also ensure same upscale factor
                //can be used in x direction as y direction when writing waypoints out to file
                if (aspect_ratio_image == aspect_4_3)
                {
                    //Change aspect map ratio if required
                    if (aspect_ratio_map != aspect_4_3)
                    {
                        changeMapAspectRatio(eAspectRatio.fourThree);
                    }
                }
                else if (aspect_ratio_image == aspect_16_9)
                {
                    //Change aspect map ratio if required
                    if (aspect_ratio_map != aspect_16_9)
                    {
                        changeMapAspectRatio(eAspectRatio.sixteenNine);
                    }
                }

                //Add image to map
                this.map.Image = image;

                //Update scale factor
                this.scale_factor = (Convert.ToDouble(map.Width) / image.Width);

                //Enable load waypoints file button now we have a non-zero scale factor calculated
                this.enableLoadFile();

                //Enable save waypoints file button only if we have at least one waypoint to save
                if (waypoints.Count > 0)
                {
                    this.enableWriteFile();
                }

                this.writeLogLine("Successfully loaded map image \"" + filename + "\" !");
            }
            
        }

        private void fileMenuLoadWaypoints_Click(object sender, EventArgs e)
        {
            //Reset the form ready for loading waypoints
            this.resetAll();

            //Display open file dialog
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Filter = "Text files(*.txt) | *.txt| All files(*.*) | *.*";
            fileDialog.RestoreDirectory = false;

            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                //TO DO: For better design, consider moving all waypoint file processing into Waypoints class as per the writing to a waypoint file
                String filename = fileDialog.FileName;
                String line = "";
                int line_num = 1;
                int x = 0;
                int y = 0;
                int speed = 0;
                int size = 0;
                eDirection dir = 0;
                StreamReader streamReader = null;

                //Read in text file
                try
                {
                    //Create streamreader to read in specified file
                    streamReader = new StreamReader(filename, Encoding.ASCII);

                    try
                    {
                        //Parse lines until end of file
                        while (streamReader.Peek() > 0)
                        {
                            line = streamReader.ReadLine();

                            //If we have a comment line, skip
                            if (line.ElementAt(0) == '#') continue;

                            char[] separator = new Char[] {','};
                            String[] fields = line.Split(separator);

                            if (fields.Length != 5) //Check if incorrect number of fields
                            {
                                this.writeLogLine("Read Error: Invalid waypoint format in line " + line_num + " of \"" + filename + "\" !");
                             
                                line_num++;
                                continue;//Invalid line, skip
                            }

                            try //Try to convert fields into expected types
                            {
                                x = Convert.ToInt32(fields[0]);
                                y = Convert.ToInt32(fields[1]);
                                speed = Convert.ToInt32(fields[3]);
                                size = Convert.ToInt32(fields[4]);
                                dir = (eDirection)Enum.Parse(typeof(eDirection), fields[2]);

                                if (!Enum.IsDefined(typeof(eDirection), dir))
                                {
                                    throw new System.FormatException("File line direction field does not match eDirection enumerator");
                                }

                            }

                            catch //Error in type conversion of the fields
                            {
                                this.writeLogLine("Read Error: Waypoint line " + line_num + " invalid format in \"" + filename + "\" !");

                                line_num++;
                                continue;//Invalid line, skip
                            }

                            Waypoint wp = new Waypoint();

                            //Must scale back down the waypoint x/y values from file "real-world" co-ordinate system to
                            //map co-ordinate system
                            wp.x = Convert.ToInt32(x * this.scale_factor);
                            wp.y = Convert.ToInt32(y * this.scale_factor);
                            wp.size = Convert.ToInt32(size * this.scale_factor);
                            wp.direction = dir;
                            wp.speed = speed;
                            
                            //Add new waypoint to waypoints list
                            this.waypoints.addWp(wp);
                            
                            line_num++;
                        }
                            
                    }
                    catch
                    {
                        this.writeLogLine("Read Error: IO failure in reading waypoint line " + line_num + " from \"" + filename + "\" !");
                    }


                }
                catch
                {
                    this.writeLogLine("Read Error: Failed to open \"" + filename + "\" ! Check it is a valid .txt file...");
                }
                finally
                {
                    streamReader.Close();
                }

                this.writeLogLine("Waypoint file \"" + filename + "\" loaded.");

                //Redraw map with read in waypoints
                this.map.Invalidate();

                //Put in edit mode and activate buttons
                if(waypoints.Count >0)
                {
                    this.mode = eMode.Edit;
                    this.disableEdit();
                    this.enableMove();
                    this.enableDelete();
                    this.enableWriteFile();
                }
            }

            
        }

        /*private void aspectRatioMenuFourThree_Click(object sender, EventArgs e)
        {
            if(this.aspectRatio == eAspectRatio.sixteenNine) //If we need to change aspect ratio
            {
                //Warn user they will lose map image and waypoints
                DialogResult result = MessageBox.Show("Warning:  Changing aspect ratio will clear all waypoints and the current map image.\n\nDo you wish to continue?",
                    "Data Loss Warning",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning);

                if(result == DialogResult.Yes)
                {
                    this.changeMapAspectRatio(eAspectRatio.fourThree);

                    //Update check boxes to show selection
                    this.aspect43MenuItem.Checked = true;
                    this.aspect169MenuItem.Checked = false;

                    //Reset form
                    this.resetAll();

                    //Clear map image
                    this.map.Image = null;
                }
            }
        }*/

        /*private void aspectRatioMenuSixteenNine_Click(object sender, EventArgs e)
        {
            if (this.aspectRatio == eAspectRatio.fourThree) //If we need to change aspect ratio
            {
                //Warn user they will lose map image and waypoints
                DialogResult result = MessageBox.Show("Warning:  Changing aspect ratio will clear all waypoints and the current map image.\n\nDo you wish to continue?",
                    "Data Loss Warning",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning);

                if (result == DialogResult.Yes)
                {
                    this.changeMapAspectRatio(eAspectRatio.sixteenNine);

                    //Update check boxes to show selection
                    this.aspect169MenuItem.Checked = true;
                    this.aspect43MenuItem.Checked = false;
                   
                    //Reset form
                    this.resetAll();

                    //Clear map image
                    this.map.Image = null;
                }
            }
        }*/

        private void fileMenuSaveWaypoints_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveDialog = new SaveFileDialog();

            saveDialog.Filter = "Text files(*.txt) | *.txt| All files(*.*) | *.*";
            saveDialog.RestoreDirectory = false;
            try
            {
                if (saveDialog.ShowDialog() == DialogResult.OK)
                {
                    String filename = saveDialog.FileName;
                    if (this.waypoints.writeToFile(filename, this.scale_factor) == 0)
                    {
                        this.writeLogLine("Successfully wrote waypoints to \"" + filename + "\" !");
                    }
                    else
                    {
                        this.writeLogLine("Error: Failed to write waypoints to \"" + filename + "\" !");
                    }
                }
            }

            catch
            {
                this.writeLogLine("Error: Could not locate specified file for writing! Check it exists.");
            }
        }

        private void fileMenuSettings_Click(object sender, EventArgs e)
        {
            SettingsForm SettingsDialog = new SettingsForm();

            //Open up a modal dialog to set server settings
            SettingsDialog.ShowDialog(this);

            //Dispose the form (mark it for garbage collection)
            SettingsDialog.Dispose();
        }

        #endregion

        #endregion

        #region Form Control Validation
       
        private void waypointSpeedTextBox_Validating(object sender, CancelEventArgs e)
        {
            string error_str;
            TextBox textBox = (TextBox)sender;

            if (!ValidSpeed(textBox.Text, out error_str))
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

        private void waypointRadiusTextBox_Validating(object sender, CancelEventArgs e)
        {
            string error_str;
            TextBox textBox = (TextBox)sender;

            if (!ValidSize(textBox.Text, out error_str))
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

        private void TextBox_Validated(object sender, EventArgs e)
        {
            TextBox textBox = (TextBox)sender;

            //Successfuly validated, clear error
            errorProvider1.SetError(textBox, "");
            textBox.BackColor = Color.White;
        }

        private bool ValidSpeed(String speed, out string error_str)
        {
            int i=0;

            if(speed.Length == 0)
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
            if (i< 1 || i>100)
            {
                error_str = "Speed must be a integer number in range 1-100!";
                return false;
            }

            //If here, speed is valid
            error_str = "";
            return true;
        }

        private bool ValidSize(String size, out string error_str)
        {
            int i = 0;

            if (size.Length == 0)
            {
                error_str = "You must enter an integer size in range 1-1000!";
                return false;
            }

            if (!int.TryParse(size, out i))
            {
                error_str = "Size must be a integer number in range 1-1000!";
                return false;
            }

            //If here, size is an integer, check its range
            if (i < 1 || i > 1000)
            {
                error_str = "Size must be a integer number in range 1-1000!";
                return false;
            }

            //If here, size is valid
            error_str = "";
            return true;
        }

        #endregion

    }
}
