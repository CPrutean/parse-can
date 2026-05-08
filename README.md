# Overview

This project was a personal script that I was using to debug the myactuator RMDx8 x8-25 series motors. While working with these motors I developed this script alongside with the test_translation.txt file which takes in logs from `candump` the `test_translation.txt` file is translation file that i used which describes different messages

> [NOTE]
> make sure to compile the `hex_translator.c` with whatever C compiler of your choice to `hex_to_int` since the can parser is dependent on that

## The workflow

There are 2 distinct steps for the workflow Extraction and parsing

### Extraction

If the can line is running remotely run `ssh <user>@<IP> "candump <can-interface>" > <temp-filename>` that way you have a file on your machine to use
If you are running it locally then `candump any > <temp-filename>` should suffice

### Parsing

To actually be able to parse the actual canlogs you need to have a populated translation file, if you are making a new translation file in the future whether thats by hand or with AI make sure that you pass it the same initial `test_translation.txt` file as the example. The script will not work otherwise

then simply run `parse_can -t <translation-file> -f <canlog-file>` and you should be able to translate logs
