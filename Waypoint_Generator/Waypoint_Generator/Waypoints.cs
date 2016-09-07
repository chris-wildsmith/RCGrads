using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Reflection;


namespace Waypoint_Generator
{

    #region Enums

    public enum eDirection { Forwards, Backwards };

    #endregion

    #region Classes

    public class Waypoints
    {
        
        #region Variables

        //The internal private master list of waypoints
        private List<Waypoint> _waypoints;
        // Bool indicating if a waypoint is currently selected
        private bool selected;
        //Index of currently selected waypoint (Set to -1 if no waypoint selected)
        private int wp_selected_index;

        private TextBox logBox;
        #endregion

        #region Constructor

        public Waypoints(TextBox logBox)
        {
            this.logBox = logBox;
            _waypoints = new List<Waypoint>();
            wp_selected_index = -1; //No waypoint selected at startup
        }

        #endregion

        #region Properties
        //Property to return a reference to a read-only wrapper object around the internal waypoints list
        //Idea from http://stackoverflow.com/questions/4749021/listt-readonly-with-a-private-set
        public IReadOnlyCollection<Waypoint> waypoints
        {
            get { return _waypoints.AsReadOnly();}
        }

        public int Count
        {
            get { return _waypoints.Count(); }
        }

        public bool isSelected
        {
            get { return selected; }
        }

        public int selected_idx
        {
            get { return wp_selected_index; }
        }
        #endregion


        #region Events
        /// <summary>
        /// Event raised when all waypoints have been removed from the waypoints list
        /// </summary>
        public event EventHandler waypointsEmpty;
        /// <summary>
        /// Event raised when a waypoint has been added to the waypoints list
        /// </summary>
        public event EventHandler waypointAdded;
        #endregion

        #region Event Raiser Methods

        /// <summary>
        /// Raises the waypointsEmpty event
        /// </summary>
        protected virtual void OnWaypointsEmpty(EventArgs e)
        {
            //If there are event subscribers, raise the event
            if (waypointsEmpty != null)
            {
                waypointsEmpty(this, e);
            }
        }

        /// <summary>
        /// Raises the waypointAdded event
        /// </summary>
        protected virtual void OnWaypointAdded(EventArgs e)
        {
            //If there are event subscribers, raise the event
            if (waypointAdded != null)
            {
                waypointAdded(this, e);
            }
        }

        #endregion

        #region Public Methods

        public void addWp(Waypoint waypoint)
        {
            //Add the waypoint to the waypoints list
            _waypoints.Add(waypoint);

            //Raise waypointAdded event
            OnWaypointAdded(EventArgs.Empty);

            this.writeLogLine("Waypoint " + ( _waypoints.Count - 1) + " added: " + waypoint.ToString());
        }

        public void removeWp(int wp_idx)
        {
            if (_waypoints.Count > 0)
            {
                _waypoints.RemoveAt(wp_idx);

                //Raise waypointsEmpty event if all waypoints have now been removed
                if (_waypoints.Count == 0)
                {
                    OnWaypointsEmpty(EventArgs.Empty);
                }

                this.writeLogLine("Waypoint " + wp_idx + " removed");
            }
            else
            {
                this.writeLogLine("No waypoints to remove!");
            }
        }

        public void removeLastWp()
        {

            if (_waypoints.Count > 0)
            {
                int wp_idx = _waypoints.Count - 1;
                _waypoints.RemoveAt(_waypoints.Count-1);

                //Raise waypointsEmpty event if all waypoints have now been removed
                if(_waypoints.Count == 0)
                {
                    OnWaypointsEmpty(EventArgs.Empty);
                }

                this.writeLogLine("Waypoint " + wp_idx + " removed");
            }
            else
            {
                this.writeLogLine("No waypoints to remove!");
            }
        }

        public void removeAll()
        {
            if (_waypoints.Count != 0)
            {
                _waypoints.Clear();

                //Raise waypointsEmpty event
                OnWaypointsEmpty(EventArgs.Empty);

                this.writeLogLine("All waypoints cleared!");
            }
        }

        public void updateWp(int wp_idx, int x, int y, int speedToWp, eDirection directionToWp, int size)
        {
            _waypoints[wp_idx].x = x;
            _waypoints[wp_idx].y = y;
            _waypoints[wp_idx].speed = speedToWp;
            _waypoints[wp_idx].direction = directionToWp;
            _waypoints[wp_idx].size = size;
            this.writeLogLine("Waypoint " + wp_idx + " updated: " + _waypoints[wp_idx].ToString());
        }

        public void updateLocation(int wp_idx, int x, int y)
        {
            _waypoints[wp_idx].x= x;
            _waypoints[wp_idx].y = y;

        }

        public void updateSpeed(int wp_idx, int speedToWp)
        {
            _waypoints[wp_idx].speed = speedToWp;
            this.writeLogLine(
                "Waypoint " + wp_idx
                + " speed updated: "
                + _waypoints[wp_idx].speed);
        }

        public void updateDirection(int wp_idx, eDirection directionToWp)
        {
            _waypoints[wp_idx].direction = directionToWp;
            this.writeLogLine(
                "Waypoint " + wp_idx
                + " direction updated: "
                + _waypoints[wp_idx].direction.ToString());
        }

        public void updateSize(int wp_idx, int size)
        {
            _waypoints[wp_idx].size = size;
            this.writeLogLine(
                "Waypoint " + wp_idx
                + " size updated: "
                + _waypoints[wp_idx].size);
        }

        public Waypoint getWaypoint(int wp_idx)

        {
            //Return a reference to a clone of the waypoint at the specified index to prevent changes to the clone affecting the original
            Waypoint wp_clone = _waypoints[wp_idx].Clone();
            return wp_clone;
        }

        public void selectWaypoint(int wp_idx)
        {
            selected = true;
            wp_selected_index = wp_idx;

            for (int i = 0; i < _waypoints.Count(); i++)
            {
                //Select only the selected waypoint and deselect all other waypoints
                if (i == wp_idx)
                {
                    _waypoints[i].selected = true;
                }
                else
                {
                    _waypoints[i].selected = false;
                }
            }

        }

        public void deselectAll()
        {
            selected = false;
            wp_selected_index = -1;
            foreach (Waypoint wp in _waypoints)
            {
                wp.selected = false;
            }
        }

        public int findClosest(Point point, int threshold)
        {
            //Returns index of waypoint in list that is closest to input point AND within supplied threshold distance (pixels)

            if (Properties.Settings.Default.debug)
            {
                Console.WriteLine("Finding closest waypoint to (" + point.X + "," + point.Y +
                        ") within user-specified " + threshold.ToString() + " pixel threshold...");
            }

            double x_dist, y_dist, dist, closest_dist;
            int idx, closest_idx;
            idx = 0;
            closest_dist = 10000; //Arbitraly large value to start
            closest_idx = 0;
            bool match_found = false;

            foreach (Waypoint wp in _waypoints)
            {
                
                x_dist = Convert.ToDouble(Math.Abs(point.X - wp.x));
                y_dist = Convert.ToDouble(Math.Abs(point.Y - wp.y));

                dist = Math.Sqrt((x_dist * x_dist) + (y_dist * y_dist));

                if (Properties.Settings.Default.debug)
                {
                    Console.WriteLine("Dist " + idx.ToString() + ": " + dist.ToString());
                }

                if (dist <= threshold)
                {
                    match_found = true;

                    if (dist < closest_dist)
                    {
                        closest_idx = idx;
                    }

                }
                idx++;
            }
            
            if (match_found)
            {
                if (Properties.Settings.Default.debug)
                {
                    Console.WriteLine("Waypoint " + closest_idx.ToString() +
                    " at (" + _waypoints[closest_idx].x + "," + _waypoints[closest_idx].y +
                    ") is closest waypoint to (" + point.X + "," + point.Y +
                    ") within user-specified " + threshold.ToString() + " pixel threshold");
                }

                return closest_idx;
            }
            else
            {
                if (Properties.Settings.Default.debug)
                {
                    Console.WriteLine("No closest waypoint to (" + 
                    point.X + "," + point.Y +
                    ") within user-specified " + threshold.ToString() + " pixel threshold");
                }
                return -1; //No waypoint found

            }
                
        }

        public void writeLogLine(string log_string)
        {
            this.logBox.AppendText(log_string + Environment.NewLine);

        }

        public int writeToFile(string filename, double scale_factor)
        {
            
            
            int scaled_x = 0;
            int scaled_y = 0;
            int scaled_size = 0;

            StreamWriter streamWriter = null;

            try
            {
                //Create streamwriter for specified filename. Overwrite any existing file
                streamWriter= new StreamWriter(filename, false, Encoding.ASCII);

                //Write header info to file
                string name = AppDomain.CurrentDomain.FriendlyName;
                string version = Assembly.GetEntryAssembly().GetName().Version.ToString();
                string time = DateTime.Now.ToString();
                string user = System.Security.Principal.WindowsIdentity.GetCurrent().Name;

                string header_row = string.Format("#Auto-generated by {0} v{1} on {2} by {3}", name, version, time, user);
                streamWriter.WriteLine(header_row);

                //Write waypoints to file
                string lineToWrite = "";
                foreach (Waypoint wp in _waypoints)
                {
                    //Map image is compressed to fit GUI, must scale back up
                    scaled_x = Convert.ToInt32(wp.x * (1/scale_factor));
                    scaled_y = Convert.ToInt32(wp.y * (1/scale_factor));
                    scaled_size = Convert.ToInt32(wp.size * (1/scale_factor));

                    lineToWrite = scaled_x + "," + scaled_y + "," + wp.direction.ToString() + "," + wp.speed + "," + scaled_size;

                    streamWriter.WriteLine(lineToWrite);
                }

                return 0;
            }
            catch
            {
                this.writeLogLine("Error: Failed to open " + filename + " for writing!");
                return -1;
            }
            finally
            {
                streamWriter.Close();
            }
        }

        #endregion

    }

    //Maybe change this Waypoint class to a simple struct?
    public class Waypoint
    {
        private int speedToWp;
        private eDirection directionToWp;
        private Point point;
        private int _size;
        private bool _selected;

        #region Constructors

        public Waypoint()
        {
            this.point.X = 0;
            this.point.Y = 0;
            this.speedToWp = 0;
            this.size = 10;
            this.directionToWp = eDirection.Forwards;
            this._selected = false;
        }

        public Waypoint(int x, int y, int speedToWp, eDirection directionToWp, int size)
        {
            this.point.X = x;
            this.point.Y = y;
            this.speedToWp = speedToWp;
            this.size = size;
            this.directionToWp = directionToWp;
            this._selected = false;
        }

        #endregion

        #region Properties
        public int x
        {
            get { return this.point.X; }
            set { this.point.X = value; }
        }

        public int y
        {
            get { return this.point.Y; }
            set { this.point.Y = value; }
        }

        public int speed
        {
            get { return this.speedToWp; }
            set { this.speedToWp = value; }
        }

        public eDirection direction
        {
            get { return this.directionToWp; }
            set { this.directionToWp = value; }
        }

        public int size
        {
            get { return this._size; }
            set { this._size = value; }
        }

        public bool selected
        {
            get { return this._selected; }
            set { this._selected = value; }
        }

        #endregion

        #region Public Methods

        public override string ToString()
        {
            return "X: " + this.point.X + ", Y: " + this.point.Y + ", Speed: " + this.speedToWp + ", Direction: " + this.directionToWp.ToString() + ", Radius: " + this.size;
        }

        public Waypoint Clone()
        {
            Waypoint wp_copy = (Waypoint)this.MemberwiseClone();
            /*
            - This is a shallow copy of the original waypoint.
            - Only value types are copied to new values.
            - Any reference types (objects and strings etc.) are still set to the same reference as the original
            - e.g. The point object in the copy is a copy of the reference to the original object's point object
            - We must overwrite the point object reference in the clone with a reference to a new point object with the same x, y member variables
            - This prevents changes to the point in the clone from changing the point object in the original waypoint in the list
            - https://msdn.microsoft.com/en-us/library/system.object.memberwiseclone(v=vs.110).aspx
             * - https://msdn.microsoft.com/en-us/library/4d43ts61(v=vs.90).aspx
             */

            wp_copy.point = new Point(this.point.X, this.point.Y);

            return wp_copy;

        }

        #endregion

    }

    #endregion

}
