# Harvey-AES
## How it works
Harvey-AES encrypts files using base64 encoding and AES(rijndael cipher). It's also named after my dog Harvey.
![alt text](https://github.com/GRIM-OPS/Harvey-AES/blob/master/harvey.jpg)
## Getting it up and running
### Compiling
You must have gcc installed!
```
chmod u+x install.sh
./install.sh
harvey --gen
```
This script will compile the code into an exexutable named harvey and move it into the /usr/bin/ directory making it possible to use it as a command. You don't have to use the harvey --gen command but you do have to have a file with 16 characters in it to be able to use the tool.
### Using
```
harvey --help
```
This command will bring up a help menu.
```
harvey --file test.txt --key key.txt --mode e
```
This command shows all the proper options you need to have to be able to encrpyt the test.txt file. Changing the mode from e to d will decrypt the file instead of encrypting it.
