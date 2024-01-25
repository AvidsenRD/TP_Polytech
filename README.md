# Moria Ought to Refine Interfaces Access

*Moria* is a set of client libraries for the **Avidsen ONE Server** interfaces.
It eases the interaction with the server for the humans as well as the machines.

## Bash

The **Bash** script `moria.sh` is a simple interactive shell for *Dain*, *Dis*
and *Durin* requests.

### Usage

`moria.sh` takes exactly one argument, the server address.

    Usage: ./moria.sh <server>

When launched, the script enters a forever loop to execute the following
sequence: display a prompt, read for commands on the standard input, and then
parse and execute them. To leave the loop, press Ctrl-C.

The available commands depend on the context. The default context is *moria*.
Possible contexts are *dain*, *dis* or *durin*. To change the current context,
simple type its name: the prompt will be updated accordingly. To send a command
for another context, prefix the command with the context name.

Before any other request can be sent to the server, the user must be
authenticated. The *dain* context provide a command to ease this step:

    dain login <login> <passwd>

Here is a short session demonstrating the authentication, a context swap and a
simple Durin request:

    $ ./moria.sh  https://donkey.athemium.com
    [donkey.athemium.com] moria > dain login demo@avidsen.com "demo;passwd"
    {
        "login": "demo@avidsen.com",
        "roles": [
            "ROLE_EXEC",
            "ROLE_SCRIPT",
            "ROLE_CONFIG",
            "ROLE_ASSOCIATION",
            "ROLE_SCHEDULE",
            "ROLE_REGISTER",
            "ROLE_READ"
        ],
        "token": " eyJraWQiOiIxZTRhNjAzMy02NGI5LTRiNjQtOGViZS0xNWE4OWNmZGViOGEiLCJhbGciOiJSUzI1NiJ9.eyJzdWIiOiJkZW1vQGF2aWRzZW4uY29tIiwidWlkIjoxMCwibmJmIjoxNjc1OTUzNjA2LCJzY29wZSI6IlJPTEVfRVhFQyBST0xFX1NDUklQVCBST0xFX0NPTkZJRyBST0xFX0FTU09DSUFUSU9OIFJPTEVfU0NIRURVTEUgUk9MRV9SRUdJU1RFUiBST0xFX1JFQUQiLCJpc3MiOiJodHRwczpcL1wvZG9ua2V5LmF0aGVtaXVtLmNvbSIsIm5hbWUiOiJkZW1vQGF2aWRzZW4uY29tIiwiZXhwIjoxNjc1OTc1MjA2LCJpYXQiOjE2NzU5NTM2MDZ9.O5Io_FE2Xh6c0fN5H4J-TJv3DWp0_auZdC8EpRtaQI16OjBoxqRGW6-oDagyKLucSC_CeLtxmgDdbm08f4PZBTYx550jSU-IYc-sbUwBAiwBWu5wPYOLGevqJXg_G0STxFYsM2ZfbYjyqyu2wl893Sd7nVGo2qmlB-iUcu4L3ZW4LRTs5y0llcYRNAVuLsKjZ3xtMGDXkuJTz_OGq_2uhc8ZBXlIDA_41vIqJ_MVZhmnOT18FrIolc4dSd8VupvWY2iyoJFgHOvu-ZTfPHxXA8nQiBrgC3yjTRAkaFyxqidmJpsAhn6M2vOKA_Xio838yeGgzj2vm01CotMrhHDqOw",
        "userId": 10,
        "userName": "demo@avidsen.com"
    }
    
    
    demo[donkey.athemium.com] moria > durin
    demo[donkey.athemium.com] durin > get /
    {
        "resource": {
            "ass": "https://donkey.athemium.com/services/durin/ass",
            "my": "https://donkey.athemium.com/services/durin/my",
            "server": "https://donkey.athemium.com/services/durin/server",
            "version": "2.0a"
        },
        "uri": "https://donkey.athemium.com/services/durin/"
    }

    
    demo[donkey.athemium.com] durin] > ^C
    History saved


### Commands History

The shell relies on **readline** to read the user commands. A visible effect is
that some characters must be protected or they will be considered as separators
in the arguments. See how the password is quoted in the example above to protect
the semicolon.

The inputs history is stored in `$XDG_CACHE_HOME/ao-history`.

### Environment

The script is aware of the name used on the command line. For example, if it is
executed through a logical link named `durin[.*]`, then the initial context will
be *durin*.

`AO_MORIA_DISPLAY` is used to alter the output of **httpie** on HTTP requests
and responses. See the description of the `--print` argument in man page `http(1)`.

`XDG_CACHE_HOME` is used to locate the history of commands. Default is `~/.cache`.

## Prerequisites

### Install Python 3 on your OS

#### Linux OS

Python is already pre-install on most of the linux distribution.
To check if python3 is install type :

    python3 --version

For Linux Operating System with Debian or Ubuntu distribution, if python is not
installed do the following steps, with **apt** packages manager:

1. Update the Package Repository
  
        sudo apt update
      
2. Install Python
  
        sudo apt install python3
      
3. Verify Installation
  
        python3 --version
      
For Debian, Ubuntu other Linux distribution, you can check **Python** official
documentation [here](https://docs.python.org/fr/3/using/unix.html#on-linux).

#### Windows OS

You can refer to **Python** official documentation for [installation on Windows](https://docs.python.org/fr/3/using/windows.html).

### Install jq

#### Linux OS

For Linux Operating System with Debian or Ubuntu distribution,
execute the following steps, with **apt** packages manager:

1. Update the Package Repository
  
        sudo apt update
      
2. Install jq
  
        apt install -y jq

3. Verify Installation
  
        jq --version
      
For Debian, Ubuntu other Linux distribution, you can check **jq** official
documentation [here](https://jqlang.github.io/jq/download/).

#### Windows OS

You can refer to **jq** offiical documentation for [installation on Windows](https://jqlang.github.io/jq/download/).

### Install httpie

#### Linux OS

For Linux Operating System with Debian or Ubuntu distribution,
execute the following steps, with **apt** packages manager:

1. Add httpie remote Package Repository to Package Repository
  
        curl -SsL https://packages.httpie.io/deb/KEY.gpg | sudo gpg --dearmor -o /usr/share/keyrings/httpie.gpg
        sudo echo "deb [arch=amd64 signed-by=/usr/share/keyrings/httpie.gpg] https://packages.httpie.io/deb ./" > /etc/apt/sources.list.d/httpie.list
      
2. Update the Package Repository
  
        apt install -y jq
      
3. Install httpie
  
        sudo apt install httpie
      
4. Verify Installation
  
        http --version
      
For Debian, Ubuntu other Linux distribution, you can check **httpie** official
documentation [here](https://httpie.io/docs/cli/linux).

#### Windows OS

You can refer to **jq** official documentation for [installation on Windows](https://httpie.io/docs/cli/windows).

## Add a MQTT object/product to your Avidsen One server user account

1. Set current directory to directory where **moria.sh** is copied.

        $ cd <work_dir>
    
2. Launch moria **Bash** script.

        $ ./moria.sh  https://donkey.athemium.com
    
3. Authenticate with the credential of the user that has been registred with the Mobile App.

        [donkey.athemium.com] moria > dain login '<user_login>' '<user_password>'
    
4. Switch to durin context

        <user_login>[donkey.athemium.com] moria > durin
    
5. Create a new product

        <user_login>[donkey.athemium.com] durin > post /my/objects name='<user_name>' realName='<object_type>/<object_reference>/<mqtt_client_id>' typeName='<object_type_id>'
    
    Example:
  
        <user_login>[donkey.athemium.com] durin > post /my/objects name='Office Light' realName='light/light_rgb/ID66' typeName='AtHomeLight'


Then you can plug/power on the objects and they should register to the Avidsen One server to the Raspberry "box".