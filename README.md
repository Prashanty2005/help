# help

Phase 1: Configure AWS Security Group
Before connecting to your server, you must open the necessary ports in your AWS console so web traffic can reach your application.

Go to your AWS EC2 Dashboard > Instances > Select your instance.

Go to the Security tab and click on the Security Group.

Click Edit inbound rules and add the following:

SSH (Port 22): Source 0.0.0.0/0 (Allows terminal access)

Custom TCP (Port 5000): Source 0.0.0.0/0 (Allows Backend API access — change if your backend uses a different port)

Custom TCP (Port 5173 or 3000): Source 0.0.0.0/0 (Allows Frontend access — 5173 for Vite, 3000 for Create React App)


Phase 2: Connect to EC2 and Install Server Dependencies
Open your local terminal (PowerShell, Command Prompt, or Mac/Linux Terminal), navigate to where your .pem key is stored, and log in.

1. Connect to your EC2 instance
ssh -i <your-key.pem> ec2-user@<your-ec2-public-ip>

2. Update the system packages
sudo dnf update -y

3. Add the Node.js repository (Using LTS version 20)
curl -fsSL https://rpm.nodesource.com/setup_20.x | sudo bash -

4. Install Node.js and Git
sudo dnf install -y nodejs git

5. Verify the installations
node -v
npm -v
git --version


Phase 3: Clone Your Repository
Download your application code from GitHub onto the EC2 instance.


1. Clone your project
git clone <your-github-repo-url>

2. Move into your project directory
cd <your-project-folder>


Phase 4: Backend Setup & PM2 (Process Manager)
Since you are using MongoDB Atlas, you don't need to install a database on the server. You only need to provide the Atlas connection string in your environment variables.


1. Navigate to the backend folder
cd backend

 2. Install backend dependencies
npm install

3. Create and edit the environment variables file
nano .env


Inside the nano editor, add your configuration:
(Make sure to replace the placeholder with your actual Atlas string and password)

PORT=5000
MONGO_URI=mongodb+srv://<username>:<password>@cluster0.mongodb.net/<database_name>?retryWrites=true&w=majority

(To save: Press Ctrl + O, then Enter, then Ctrl + X)

Start the Backend in the background:
To ensure your backend keeps running even after you close the terminal, use PM2.

1. Install PM2 globally
sudo npm install -g pm2

2. Start your backend server (replace server.js with your entry file if different, e.g., index.js)
pm2 start server.js --name "my-backend"

3. Ensure PM2 restarts if the server reboots
pm2 startup
pm2 save

Phase 5: Frontend Setup
Now, open a second terminal to handle the frontend, or navigate back out of the backend folder in your current terminal.


1. Navigate to the frontend folder
cd ../frontend

2. Install frontend dependencies
npm install

3. Create and edit the frontend environment variables file
nano .env
Inside the nano editor, link your frontend to your backend:
(Use REACT_APP_... instead of VITE_... if you used Create React App instead of Vite)

Plaintext
VITE_BACKEND_BASE_URL=http://<your-ec2-public-ip>:5000
(To save: Press Ctrl + O, then Enter, then Ctrl + X)

Run the Frontend:
If you are using Vite, you must expose the host so it can be accessed over the internet:

Bash
npm run dev -- --host
(If you are using Create React App, simply run npm start)

Phase 6: Final Access
Your MERN application is now live. Open your web browser and navigate to:

Plaintext
http://<your-ec2-public-ip>:<your-frontend-port>
(e.g., [http://51.21.180.226:5173](http://51.21.180.226:5173))
