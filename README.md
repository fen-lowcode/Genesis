#### 

`for educational purposes only`

```
Type: Backdoor
Version: 1.0

Tested AV

Windows Defender: N/A
```

---

A reverse-shell that uses Discord bot API for it's mode of communication.
Leveraging the use of Discord API thru DPP [https://dpp.dev/](https://dpp.dev/).

The malware runs in a linux machine as a daemon and connects to a discord bot using the bot's TOKEN `"MTQ2MzA4NjA3MDE4NTg1Mjk4Mw.GG5SEp.3dMl7Hxz5vbRc2-w-O54gVI1l1EuTE2xw2AQUw"` 

Upon the malware's execution it will automatically activates th bot and will now start waiting for responses in a private discord server where the attacker can send commands by using /command <SHELL COMMANDS HERE>

Upon receiving commands, it will execute it in a shell using popen() function and directs the output back to the server, for now the output has a limit of no more than 2000 characters.

This is for educational purposes only.

---

###### Improvements tips:

   *  Obfuscate the token with xor and rot decoders and decode at runtime
   *  Shrink file in size

---