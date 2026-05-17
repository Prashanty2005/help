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

3. Update the system packages

sudo dnf update -y

5. Add the Node.js repository (Using LTS version 20)

curl -fsSL https://rpm.nodesource.com/setup_20.x | sudo bash -

7. Install Node.js and Git

sudo dnf install -y nodejs git

9. Verify the installations
   
node -v
npm -v
git --version


Phase 3: Clone Your Repository
Download your application code from GitHub onto the EC2 instance.

1. Clone your project

git clone your-github-repo-url

3. Move into your project directory

cd your-project-folder


Phase 4: Backend Setup & PM2 (Process Manager)
Since you are using MongoDB Atlas, you don't need to install a database on the server. You only need to provide the Atlas connection string in your environment variables.


1. Navigate to the backend folder
   
cd backend

 3. Install backend dependencies
    
npm install

5. Create and edit the environment variables file
   
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

3. Start your backend server (replace server.js with your entry file if different, e.g., index.js)
   
pm2 start server.js --name "my-backend"

5. Ensure PM2 restarts if the server reboots
   
pm2 startup
pm2 save

Phase 5: Frontend Setup
Now, open a second terminal to handle the frontend, or navigate back out of the backend folder in your current terminal.


1. Navigate to the frontend folder
   
cd ../frontend

3. Install frontend dependencies
   
npm install

5. Create and edit the frontend environment variables file
   
nano .env
Inside the nano editor, link your frontend to your backend:
(Use REACT_APP_... instead of VITE_... if you used Create React App instead of Vite)


VITE_BACKEND_BASE_URL=http://your-ec2-public-ip:5000
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












Windows PowerShell
Copyright (C) Microsoft Corporation. All rights reserved.

Install the latest PowerShell for new features and improvements! https://aka.ms/PSWindows

PS C:\Users\Prashant> cd Downloads
PS C:\Users\Prashant\Downloads>  ssh -i key.pem ec2-user@13.60.58.137
The authenticity of host '13.60.58.137 (13.60.58.137)' can't be established.
ED25519 key fingerprint is SHA256:PdLtDVbuY4urJEGvZ6qRQsc1lsGtJin7caQvlARG++A.
This key is not known by any other names.
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added '13.60.58.137' (ED25519) to the list of known hosts.
   ,     #_
   ~\_  ####_        Amazon Linux 2023
  ~~  \_#####\
  ~~     \###|
  ~~       \#/ ___   https://aws.amazon.com/linux/amazon-linux-2023
   ~~       V~' '->
    ~~~         /
      ~~._.   _/
         _/ _/
       _/m/'

[ec2-user@ip-172-31-36-108 ~]$
[ec2-user@ip-172-31-36-108 ~]$ sudo dnf update -y
Amazon Linux 2023 Kernel Livepatch repository                                           308 kB/s |  38 kB     00:00
Dependencies resolved.
Nothing to do.
Complete!
[ec2-user@ip-172-31-36-108 ~]$ curl -fsSL https://rpm.nodesource.com/setup_18.x | sudo bash -
2026-05-16 13:06:47 -
===============================================================================
                            DEPRECATION WARNING
===============================================================================
Node.js 18.x is no longer actively supported!
You will not receive security or critical stability updates for this version.

You should migrate to a supported version of Node.js as soon as possible.

Please see https://nodesource.com/products/distributions for details about which
version may be appropriate for you.

The NodeSource Node.js distributions site contains
information both about supported versions of Node.js and N|Solid supported Linux
distributions. To learn more about usage, see:
https://nodesource.com/products/distributions

===============================================================================

Continuing in 10 seconds ...

2026-05-16 13:06:57 - Cleaning up old repositories...
2026-05-16 13:06:57 - Old repositories removed
2026-05-16 13:06:57 - Supported architecture: x86_64
2026-05-16 13:06:57 - Added N|Solid repository for LTS version: 18.x
2026-05-16 13:06:57 - dnf available, updating...
Node.js Packages for Linux RPM based distros - x86_64                                   3.1 MB/s | 1.0 MB     00:00
Last metadata expiration check: 0:00:01 ago on Sat May 16 13:06:57 2026.
Metadata cache created.
N|Solid Packages for Linux RPM based distros - x86_64                                   2.4 MB/s | 719 kB     00:00
Metadata cache created.
2026-05-16 13:06:58 - Repository is configured and updated.
2026-05-16 13:06:58 - You can use N|solid Runtime as a node.js alternative
2026-05-16 13:06:58 - To install N|solid Runtime, run: dnf install nsolid -y
2026-05-16 13:06:58 - Run 'dnf install nodejs -y' to complete the installation.
[ec2-user@ip-172-31-36-108 ~]$ sudo dnf install -y nodejs git
Last metadata expiration check: 0:00:05 ago on Sat May 16 13:06:58 2026.
Dependencies resolved.
========================================================================================================================
 Package                     Architecture      Version                               Repository                    Size
========================================================================================================================
Installing:
 git                         x86_64            2.50.1-1.amzn2023.0.1                 amazonlinux                   53 k
 nodejs                      x86_64            2:18.20.8-1nodesource                 nodesource-nodejs             34 M
Installing dependencies:
 git-core                    x86_64            2.50.1-1.amzn2023.0.1                 amazonlinux                  4.9 M
 git-core-doc                noarch            2.50.1-1.amzn2023.0.1                 amazonlinux                  2.8 M
 perl-Error                  noarch            1:0.17030-2.amzn2023.0.1              amazonlinux                   42 k
 perl-File-Find              noarch            1.37-477.amzn2023.0.8                 amazonlinux                   25 k
 perl-Git                    noarch            2.50.1-1.amzn2023.0.1                 amazonlinux                   41 k
 perl-TermReadKey            x86_64            2.38-9.amzn2023.0.2                   amazonlinux                   36 k
 perl-lib                    x86_64            0.65-477.amzn2023.0.8                 amazonlinux                   15 k

Transaction Summary
========================================================================================================================
Install  9 Packages

Total download size: 42 M
Installed size: 139 M
Downloading Packages:
(1/9): git-2.50.1-1.amzn2023.0.1.x86_64.rpm                                             1.3 MB/s |  53 kB     00:00
(2/9): git-core-doc-2.50.1-1.amzn2023.0.1.noarch.rpm                                     59 MB/s | 2.8 MB     00:00
(3/9): git-core-2.50.1-1.amzn2023.0.1.x86_64.rpm                                         42 MB/s | 4.9 MB     00:00
(4/9): perl-Error-0.17030-2.amzn2023.0.1.noarch.rpm                                     1.4 MB/s |  42 kB     00:00
(5/9): perl-Git-2.50.1-1.amzn2023.0.1.noarch.rpm                                        1.6 MB/s |  41 kB     00:00
(6/9): perl-File-Find-1.37-477.amzn2023.0.8.noarch.rpm                                  876 kB/s |  25 kB     00:00
(7/9): perl-TermReadKey-2.38-9.amzn2023.0.2.x86_64.rpm                                  1.4 MB/s |  36 kB     00:00
(8/9): perl-lib-0.65-477.amzn2023.0.8.x86_64.rpm                                        604 kB/s |  15 kB     00:00
(9/9): nodejs-18.20.8-1nodesource.x86_64.rpm                                             65 MB/s |  34 MB     00:00
------------------------------------------------------------------------------------------------------------------------
Total                                                                                    74 MB/s |  42 MB     00:00
Node.js Packages for Linux RPM based distros - x86_64                                    11 kB/s | 3.1 kB     00:00
Importing GPG key 0x3AF28A14:
 Userid     : "Nodesource Operations <operations@nodesource.com>"
 Fingerprint: 242B 8138 31AF 0956 2B6C 46F7 6B88 DA4E 3AF2 8A14
 From       : https://rpm.nodesource.com/gpgkey/ns-operations-public.key
Key imported successfully
Running transaction check
Transaction check succeeded.
Running transaction test
Transaction test succeeded.
Running transaction
  Preparing        :                                                                                                1/1
  Installing       : git-core-2.50.1-1.amzn2023.0.1.x86_64                                                          1/9
  Installing       : git-core-doc-2.50.1-1.amzn2023.0.1.noarch                                                      2/9
  Installing       : perl-lib-0.65-477.amzn2023.0.8.x86_64                                                          3/9
  Installing       : perl-TermReadKey-2.38-9.amzn2023.0.2.x86_64                                                    4/9
  Installing       : perl-File-Find-1.37-477.amzn2023.0.8.noarch                                                    5/9
  Installing       : perl-Error-1:0.17030-2.amzn2023.0.1.noarch                                                     6/9
  Installing       : perl-Git-2.50.1-1.amzn2023.0.1.noarch                                                          7/9
  Installing       : git-2.50.1-1.amzn2023.0.1.x86_64                                                               8/9
  Running scriptlet: nodejs-2:18.20.8-1nodesource.x86_64                                                            9/9
  Installing       : nodejs-2:18.20.8-1nodesource.x86_64                                                            9/9
  Running scriptlet: nodejs-2:18.20.8-1nodesource.x86_64                                                            9/9
  Verifying        : nodejs-2:18.20.8-1nodesource.x86_64                                                            1/9
  Verifying        : git-2.50.1-1.amzn2023.0.1.x86_64                                                               2/9
  Verifying        : git-core-2.50.1-1.amzn2023.0.1.x86_64                                                          3/9
  Verifying        : git-core-doc-2.50.1-1.amzn2023.0.1.noarch                                                      4/9
  Verifying        : perl-Error-1:0.17030-2.amzn2023.0.1.noarch                                                     5/9
  Verifying        : perl-File-Find-1.37-477.amzn2023.0.8.noarch                                                    6/9
  Verifying        : perl-Git-2.50.1-1.amzn2023.0.1.noarch                                                          7/9
  Verifying        : perl-TermReadKey-2.38-9.amzn2023.0.2.x86_64                                                    8/9
  Verifying        : perl-lib-0.65-477.amzn2023.0.8.x86_64                                                          9/9

Installed:
  git-2.50.1-1.amzn2023.0.1.x86_64                           git-core-2.50.1-1.amzn2023.0.1.x86_64
  git-core-doc-2.50.1-1.amzn2023.0.1.noarch                  nodejs-2:18.20.8-1nodesource.x86_64
  perl-Error-1:0.17030-2.amzn2023.0.1.noarch                 perl-File-Find-1.37-477.amzn2023.0.8.noarch
  perl-Git-2.50.1-1.amzn2023.0.1.noarch                      perl-TermReadKey-2.38-9.amzn2023.0.2.x86_64
  perl-lib-0.65-477.amzn2023.0.8.x86_64

Complete!
[ec2-user@ip-172-31-36-108 ~]$ git clone https://github.com/kaustubhgharat/Event_Management.git
Cloning into 'Event_Management'...
remote: Enumerating objects: 3803, done.
remote: Counting objects: 100% (3803/3803), done.
remote: Compressing objects: 100% (2809/2809), done.
remote: Total 3803 (delta 847), reused 3803 (delta 847), pack-reused 0 (from 0)
Receiving objects: 100% (3803/3803), 5.01 MiB | 22.12 MiB/s, done.
Resolving deltas: 100% (847/847), done.
[ec2-user@ip-172-31-36-108 ~]$ cd Event_Management/
[ec2-user@ip-172-31-36-108 Event_Management]$ cd backend/
[ec2-user@ip-172-31-36-108 backend]$ nano .env
[ec2-user@ip-172-31-36-108 backend]$ nano .env
[ec2-user@ip-172-31-36-108 backend]$ npm install

up to date, audited 144 packages in 2s

21 packages are looking for funding
  run `npm fund` for details

16 vulnerabilities (3 low, 5 moderate, 7 high, 1 critical)

To address issues that do not require attention, run:
  npm audit fix

To address all issues, run:
  npm audit fix --force

Run `npm audit` for details.
npm notice
npm notice New major version of npm available! 10.8.2 -> 11.14.1
npm notice Changelog: https://github.com/npm/cli/releases/tag/v11.14.1
npm notice To update run: npm install -g npm@11.14.1
npm notice
[ec2-user@ip-172-31-36-108 backend]$ node app.js
◇ injected env (2) from .env // tip: ◈ secrets for agents [www.dotenvx.com]
MongoServerError: bad auth : authentication failed
    at Connection.onMessage (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/connection.js:202:26)
    at MessageStream.<anonymous> (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/connection.js:61:60)
    at MessageStream.emit (node:events:517:28)
    at processIncomingData (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/message_stream.js:124:16)
    at MessageStream._write (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/message_stream.js:33:9)
    at writeOrBuffer (node:internal/streams/writable:392:12)
    at _write (node:internal/streams/writable:333:10)
    at Writable.write (node:internal/streams/writable:337:10)
    at TLSSocket.ondata (node:internal/streams/readable:809:22)
    at TLSSocket.emit (node:events:517:28) {
  ok: 0,
  code: 8000,
  codeName: 'AtlasError',
  connectionGeneration: 0,
  [Symbol(errorLabels)]: Set(2) { 'HandshakeError', 'ResetPool' }
}
[ec2-user@ip-172-31-36-108 backend]$ node app.js
◇ injected env (2) from .env // tip: ◈ secrets for agents [www.dotenvx.com]
MongoServerError: bad auth : authentication failed
    at Connection.onMessage (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/connection.js:202:26)
    at MessageStream.<anonymous> (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/connection.js:61:60)
    at MessageStream.emit (node:events:517:28)
    at processIncomingData (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/message_stream.js:124:16)
    at MessageStream._write (/home/ec2-user/Event_Management/backend/node_modules/mongoose/node_modules/mongodb/lib/cmap/message_stream.js:33:9)
    at writeOrBuffer (node:internal/streams/writable:392:12)
    at _write (node:internal/streams/writable:333:10)
    at Writable.write (node:internal/streams/writable:337:10)
    at TLSSocket.ondata (node:internal/streams/readable:809:22)
    at TLSSocket.emit (node:events:517:28) {
  ok: 0,
  code: 8000,
  codeName: 'AtlasError',
  connectionGeneration: 0,
  [Symbol(errorLabels)]: Set(2) { 'HandshakeError', 'ResetPool' }
}
[ec2-user@ip-172-31-36-108 backend]$ nano .env


[ec2-user@ip-172-31-36-108 backend]$ node app.js
◇ injected env (2) from .env // tip: ◈ secrets for agents [www.dotenvx.com]
MongooseServerSelectionError: Could not connect to any servers in your MongoDB Atlas cluster. One common reason is that you're trying to access the database from an IP that isn't whitelisted. Make sure your current IP address is on your Atlas cluster's IP whitelist: https://www.mongodb.com/docs/atlas/security-whitelist/
    at _handleConnectionErrors (/home/ec2-user/Event_Management/backend/node_modules/mongoose/lib/connection.js:809:11)
    at NativeConnection.openUri (/home/ec2-user/Event_Management/backend/node_modules/mongoose/lib/connection.js:784:11)
    at process.processTicksAndRejections (node:internal/process/task_queues:95:5) {
  reason: TopologyDescription {
    type: 'ReplicaSetNoPrimary',
    servers: Map(3) {
      'ac-yd81mf8-shard-00-01.okl8mjs.mongodb.net:27017' => [ServerDescription],
      'ac-yd81mf8-shard-00-02.okl8mjs.mongodb.net:27017' => [ServerDescription],
      'ac-yd81mf8-shard-00-00.okl8mjs.mongodb.net:27017' => [ServerDescription]
    },
    stale: false,
    compatible: true,
    heartbeatFrequencyMS: 10000,
    localThresholdMS: 15,
    setName: 'atlas-uoxcin-shard-0',
    maxElectionId: null,
    maxSetVersion: null,
    commonWireVersion: 0,
    logicalSessionTimeoutMinutes: null
  },
  code: undefined
}
[ec2-user@ip-172-31-36-108 backend]$ client_loop: send disconnect: Connection reset
PS C:\Users\Prashant\Downloads>


