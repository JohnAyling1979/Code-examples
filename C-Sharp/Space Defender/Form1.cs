using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Text;
using System.IO;
using System.Media;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Assignment_6
{
    public partial class Form1 : Form
    {
        //instance variables
        private Graphics screen;
        private System.Windows.Forms.Timer refreshRate;
        private Player player;
        private List<Bullet> shoots;
        private List<Enemy> enemies;
        private Random random;
        private List<int> HS;
        private int level;
        private Boolean running;
        private Boolean end;
        private Boolean hsScreen;
        private int finalScore;
        private SoundPlayer menu;
        private SoundPlayer game;
        private SoundPlayer gameover;
        private int baseLife;
        private Bitmap playerBMP;
        private Bitmap playerUpBMP;
        private Bitmap playerDownBMP;
        private Bitmap enemyBMP;
        private Bitmap bgBMP;
        private Bitmap planetBMP;
        private Bitmap explosionBMP;
        private TextureBrush metalBrush;
        private PrivateFontCollection titleFont;

        /*
         * Constructor
         */
        public Form1()
        {
            InitializeComponent();
        }

        /*
         * Ran when the form first loads
         */
        private void Form1_Load(object sender, EventArgs e)
        {
            //initualize instance variables
            LoadResources();
            random = new Random();
            screen = this.CreateGraphics(); 
            enemies = new List<Enemy>();
            HS = new List<int>();
            shoots = new List<Bullet>();
            running = false;
            end = false;
            hsScreen = false;

            //start menu music
            menu.PlayLooping();

            //check if the file exists
            if (File.Exists("scores"))
            {
                //open the file for reading
                using (StreamReader sr = new StreamReader("scores"))
                {
                    //read a line
                    String line = sr.ReadLine();

                    while(line != null)
                    {
                        String convertedLine = ConvertScore(line);
                        int score;


                        if(int.TryParse(convertedLine,out score))
                        {
                            //add it to the high score list
                            HS.Add(score);
                        }

                        //read the next line
                        line = sr.ReadLine();
                    }
                }
            }
        }

        /*
         * Called to load all the needed resources
         */
         private void LoadResources()
        {
            //music
            menu = new SoundPlayer(@"./music/menu.wav");
            game = new SoundPlayer(@"./music/game.wav");
            gameover = new SoundPlayer(@"./music/gameover.wav");

            //images
            playerBMP = new Bitmap(@"./images/playerShip.bmp");
            playerBMP.MakeTransparent(Color.Black);

            playerUpBMP = new Bitmap(@"./images/playerShipUp.bmp");
            playerUpBMP.MakeTransparent(Color.Black);

            playerDownBMP = new Bitmap(@"./images/playerShipDown.bmp");
            playerDownBMP.MakeTransparent(Color.Black);

            enemyBMP = new Bitmap(@"./images/enemyShip.bmp");
            enemyBMP.MakeTransparent(Color.Black);

            bgBMP = new Bitmap(@"./images/bg.bmp");

            planetBMP = new Bitmap(@"./images/earth.bmp");
            planetBMP.MakeTransparent(Color.Black);

            explosionBMP = new Bitmap(@"./images/explosion.bmp");
            explosionBMP.MakeTransparent(Color.Black);

            metalBrush = new TextureBrush(new Bitmap(@"./images/metal.bmp"));


            //fonts
            titleFont = new PrivateFontCollection();
            titleFont.AddFontFile(@"./fonts/SpaceCadetNF.ttf");
        }

        /*
         * Ran when the start button is clicked
         */
        private void StartButton_Click(object sender, EventArgs e)
        {
            //leave the splash sreen
            LeaveSplashScreen();

            //play the game musix
            game.PlayLooping();

            //create the player and set the level to 1
            player = new Player(playerBMP,50,250,8);
            level = 0;

            //set base's life to 100
            baseLife = 100;

            //set the running variable            
            running = true;

            //set a timmer to handle screen refresh rate
            refreshRate = new System.Windows.Forms.Timer();
            refreshRate.Interval = (1000/30); //30 FPS
            refreshRate.Tick += new EventHandler(UpdateScreen);

            //start the timer
            refreshRate.Start();
        }

        /*
         * used to turn of all the controls
         */
        private void LeaveSplashScreen()
        {
            //turn off start controls
            startButton.Visible = false;
            startButton.Enabled = false;
            highScore.Visible = false;
            highScore.Enabled = false;
            instructionButton.Visible = false;
            instructionButton.Enabled = false;
            backButton.Visible = false;
            backButton.Enabled = false;
        }

        /*
         * Called by the timer at a set interval
         */
        private void UpdateScreen(object sender, EventArgs e)
        {
            //create enemies if the wave is done
            NewEnemies();

            //checks for any collisions
            CheckCollision();

            //move all items
            MoveItems();

            //draw the screen
            DrawScreen();

            //clean up anything that has been destroyed
            CleanUp();
        }

        /*
         * called at the end of the timer tick to create enemies if needed
         */
        private void NewEnemies()
        {
            //check if all enemies have been distroyed
            if (enemies.Count == 0)
            {
                //raise the level
                level++;

                //get a random starting pos
                int y = random.Next(0, 500);

                //number of enemies for the wave
                int count = level * 10;

                //create the enemies and add them to the list
                for (int i=0;i<count;i++)
                {
                    //five per group
                    if (i % 5 == 0)
                        y = random.Next(20, 450);
                        
                    enemies.Add(new Enemy(enemyBMP, 800+i*60, y,5));
                }
            }
        }

        /*
         * called at the start to check for any collistions
         */
        private void CheckCollision()
        {
            //check each bullet
            foreach (Bullet bullet in shoots)
            {
                //compare them to each ship
                foreach (Enemy enemy in enemies)
                {
                    //check if bullet is in the enemy
                    if (bullet.Y > enemy.Y && bullet.Y < enemy.Y + 80 && bullet.X > enemy.X)
                    {
                        //kill the bullet and the enemy
                        bullet.Alive = false;
                        enemy.Alive = false;

                        //change the image of the enemy
                        enemy.Img = explosionBMP;

                        //increase player score
                        player.IncreaseScore();

                        break;
                    }
                }
            }

            //player ship collision
            foreach (Enemy enemy in enemies)
            {
                //check if ship hit the player
                if (enemy.Y + 80 > player.Y && enemy.Y < player.Y + 80 && enemy.X < player.X + 80 && enemy.X + 80 > player.X)
                {
                    //set the player as dead and update the image
                    player.Alive = false;
                    player.Img = explosionBMP;
                    break;
                }
            }
        }

        /*
         * called to move the location of all items
         */
        private void MoveItems()
        {
            //move all the enimy ships
            foreach (Enemy enemy in enemies)
            {
                enemy.Move("left");

                //if it leaves the screen mark it for clean up
                if (enemy.X < -50)
                {
                    enemy.Alive = false;
                    baseLife -= 10;
                    if (baseLife == 0)
                        player.Alive = false;                }
            }

            //move all bullets
            foreach (Bullet shot in shoots)
            {
                shot.Move();

                //if it leaves the screen mark it for clean up
                if (shot.X > 800)
                    shot.Alive = false;
            }
        }

        /*
         * called when any button is pressed
         */
        private void MoveShip(object sender, KeyEventArgs e)
        {

            //suppressed the key 
            e.SuppressKeyPress=true;

            //the player exists check the keycode
            if (player != null)
            {
                //for down
                if (e.KeyCode == Keys.Down && player.Y != 500)
                {
                    player.Move("down");
                    player.Img = playerDownBMP;
                }

                //for up
                if (e.KeyCode == Keys.Up && player.Y != 5)
                {
                    player.Move("up");
                    player.Img = playerUpBMP;
                }

                //for space
                if (e.KeyCode == Keys.Space && player.ShotDelay==0)
                    shoots.Add(player.Shoot());
            }
        }

        /*
         * used to reset the player image when the key is released
         */
        private void ResetImage(object sender, KeyEventArgs e)
        {
            if (player != null)
                player.Img = playerBMP;
        }

        /*
         * called to draw to the screen
         */
        private void DrawScreen()
        {
            //use Bitmap for second screen
            Bitmap buffer = new Bitmap(800, 600);
            Graphics bf = Graphics.FromImage(buffer);

            //clear the buffer
            bf.Clear(Color.Black);

            //if everything is running
            if (running)
            {
                //draw background
                bf.DrawImage(bgBMP, 0, 0, 800, 600);

                //draw planet
                bf.DrawImage(planetBMP, 0, 0, 100, 600);


                //draw the HUD
                bf.DrawString("Base: " + baseLife, new Font(FontFamily.GenericSansSerif, 12), Brushes.White, 100, 10);
                bf.DrawString("Score: " + player.Score, new Font(FontFamily.GenericSansSerif, 12), Brushes.White, 300, 10);
                bf.DrawString("Wave: " + level, new Font(FontFamily.GenericSansSerif, 12), Brushes.White, 500, 10);
                bf.DrawString("Enemies Remaining: " + enemies.Count, new Font(FontFamily.GenericSansSerif, 12), Brushes.White, 575, 10);


                //Draw the player ship
                bf.DrawImage(player.Img, player.X, player.Y, 80, 80);

                //Draw any enemies
                foreach (Enemy enemy in enemies)
                {
                    bf.DrawImage(enemy.Img, enemy.X, enemy.Y, 80, 80);
                }

                //Draw any bullets
                foreach (Bullet shot in shoots)
                {
                    bf.DrawImage(shot.Img, shot.X, shot.Y, 15, 5);
                }
            }
            //if gameover
            else if (end)
            {
                //draw title and score
                bf.DrawString("Game Over", new Font(FontFamily.GenericSerif, 72), Brushes.Red, 150, 175);
                bf.DrawString("Final Score:" + finalScore, new Font(FontFamily.GenericSerif, 20), Brushes.White, 275, 300);
            }
            //if the high score screen
            else if (hsScreen)
            {
                //draw the title
                bf.DrawString("High Scores", new Font(FontFamily.GenericSerif, 72), Brushes.Red, 150, 75);

                int y = 200;
                int x = 150;

                //display each score
                foreach(int score in HS)
                {
                    bf.DrawString(score.ToString(), new Font(FontFamily.GenericSerif, 24), Brushes.Red, x, y);
                    y += 50;

                    //start second column
                    if (y == 450)
                    {
                        x += 400;
                        y = 200;
                    }
                }
            }
            else
            {
                //draw background
//                bf.DrawImage(bgBMP, 0, 0, 800, 600);

                //draw the title
                bf.DrawString("Space", new Font(titleFont.Families[0], 72), metalBrush, 90, 50);
                bf.DrawString("Defender", new Font(titleFont.Families[0], 72), metalBrush, 180, 150);
            }

            //draw second screen to main
            screen.DrawImage(buffer, 0, 0);

            //free for garbage
            buffer.Dispose();
            bf.Dispose();
        }

        /*
         * overrides the OnPaint so that the images are redrawn if the screen 
         * leaves and returns focus
         */
        protected override void OnPaint(PaintEventArgs e)
        {
            // Call the OnPaint method of the base class.  
            base.OnPaint(e);

            //redraws the images
            DrawScreen();
        }

        /*
         * ran when the high score button is clickec
         */
        private void HighScore_Click(object sender, EventArgs e)
        {
            //leave from title screen
            LeaveSplashScreen();

            //turn on the back button
            backButton.Enabled = true;
            backButton.Visible = true;
            backButton.Focus();

            //set the high score screen to true
            hsScreen = true;
        }

        /*
         * called at the end of each tick to remove any unused items
         */
        private void CleanUp()
        {
            //if the player died
            if(!player.Alive)
            {
                //play gameover music
                gameover.PlayLooping();

                //save there score
                finalScore = player.Score;

                //switch the display screens
                running = false;
                end = true;

                //stop the screen refreshing
                refreshRate.Dispose();

                //dedlay before drawing the final screen
                Thread.Sleep(200);
                DrawScreen();

                //add the score to the high score list
                UpdateHSList(finalScore);

                //show the back button
                backButton.Visible = true;
                backButton.Enabled = true;

                //remove all items
                DeleteAll();
            }
            //if the player shot recently drop the delay
            else if (player.ShotDelay != 0)
            {
                player.ShotDelay--;
            }

            //remove any dead enemies
            for (int i = enemies.Count - 1; i >= 0; i--)
            {
                if (!enemies[i].Alive)
                {
                    enemies.RemoveAt(i);
                }
            }

            //remove any dead bullets
            for (int i = shoots.Count - 1; i >= 0; i--)
            {
                if (!shoots[i].Alive)
                {
                    shoots.RemoveAt(i);
                }
            }
        }

        /*
         * used to delete all elements from the game
         */
        private void DeleteAll()
        {
            //frees player for garbage collection
            player = null;

            //empties the two lists
            enemies.Clear();
            shoots.Clear();
        }

        /*
         * update the high score list
         */
        private void UpdateHSList(int score)
        {
            //add the new score to the list
            HS.Add(finalScore);

            //sort the list from largest to smallest
            HS.Sort((a, b) => -1 * a.CompareTo(b));

            //write the top ten elements to the file
            using (StreamWriter sw = new StreamWriter("scores"))
            {
                //tracks the number of scores
                int i = 0;

                //add top ten
                foreach (int outScore in HS)
                {
                    //encrypts the score and writes it to the file
                    sw.WriteLine(ConvertScore(outScore.ToString()));

                    //increase the count and breaks at 10
                    i++;
                    if (i == 10)
                        break;
                }
            }
        }

        /*
         * used to encrypt the score
         */
        private String ConvertScore(String score)
        {
            StringBuilder outScore = new StringBuilder();

            //Xors each letter
            foreach (char letter in score)
                outScore.Append((char)(letter ^ '\uFFFF'));

            //returns the new string
            return outScore.ToString();
        }

        /*
         * used to display the instruction in a message box
         */
        private void InstructionButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Space to shoot\nArrows to move up and down\n\nStop enemy ships from crashing into the planet","Controls");
        }

        /*
         * Called when the back button is clicked
         */
        private void BackButton_Click(object sender, EventArgs e)
        {
            //turns on all te controls and starts the meny music
            ShowTitleScreen();
            menu.PlayLooping();

            //turns off all the other screens
            running = false;
            end = false;
            hsScreen = false;
        }

        /*
         * used to turn on all the controls
         */
        private void ShowTitleScreen()
        {
            startButton.Visible = true;
            startButton.Enabled = true;
            startButton.Focus();
            highScore.Visible = true;
            highScore.Enabled = true;
            instructionButton.Visible = true;
            instructionButton.Enabled = true;
            backButton.Visible = false;
            backButton.Enabled = false;
        }
    }

    /*
     * This is a base class for the players and enemy
     */
    public class Ship
    {
        //instance variables
        private Bitmap img;
        private int x;
        private int y;
        private int speed;
        private Boolean alive;

        /*
         * Constructor
         */
        public Ship(Bitmap img, int x,int y,int speed)
        {
            this.img = img;
            this.x = x;
            this.y = y;
            this.speed = speed;
            alive = true;
        }
  
        /*
         * handles the movemnet for the player
         */
        public void Move(String dir)
        {
            if (dir.Equals("up"))
                Y -= speed;
            else if (dir.Equals("down"))
                Y += speed;
            else if (dir.Equals("left"))
                X -= speed;
            else if (dir.Equals("right"))
                X += speed;
        }

        //getter and setters
        public int X
        {
            get
            {
                return x;
            }
            set
            {
                x = value;
            }
        }
        public int Y
        {
            get
            {
                return y;
            }
            set
            {
                y = value;
            }
        }
        public Boolean Alive
        {
            get
            {
                return alive;
            }
            set
            {
                alive = value;
            }
        }
        public Bitmap Img
        {
            get
            {
                return img;
            }

            set
            {
                img = value;
                img.MakeTransparent(Color.Black);
            }
        }
        public int Speed
        {
            get
            {
                return speed;
            }

            set
            {
                speed = value;
            }
        }
    }

    /*
     * class for the player. It inherates from ship
     */
    public class Player : Ship
    {
        private int score;
        private int shotDelay;
        private Bitmap bulletBMP;

        /*
         * constructor
         */
        public Player(Bitmap file, int x, int y,int speed) : base(file, x, y, speed)
        {
            score = 0;
            shotDelay = 0;
            bulletBMP = new Bitmap(@"./images/bullet.bmp");
            bulletBMP.MakeTransparent(Color.Black);
        }

        /*
         * increases the players score
         */
        public void IncreaseScore()
        {
            score += 100;
        }

        /*
         * called when the player shoots
         */
        public Bullet Shoot()
        {
            //set the delay
            shotDelay = 10;

            //returns the new bullet
            return new Bullet(bulletBMP,X+80, Y+40,10);
        }

        //getters and setter
        public int ShotDelay
        {
            get
            {
                return shotDelay;
            }

            set
            {
                shotDelay = value;
            }
        }
        public int Score
        {
            get
            {
                return score;
            }
            set
            {
                score = value;
            }
        }
    }

    /*
     * class for the enemy ships. It inherates from ship
     */
    public class Enemy : Ship
    {
        //constructor
        public Enemy(Bitmap file, int x, int y,int speed) : base(file, x, y,speed)
        {
        }
    }



    public class Bullet : Ship
    {
        public Bullet(Bitmap file, int x, int y, int speed) : base(file,x,y,speed)
        {
        }

        public void Move()
        {
             X += Speed;
        }
    }
}