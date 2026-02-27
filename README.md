## Kevlar-encryption -> _IN PROGRESS_

Lightweight Encryption Software | Jamie Scott & Gus Ballman

---

**Predecessor:** [OGRE Encryption](https://github.com/GusBallmanjr/2026-CrimsonCode-Hackathon-OGRE-Encyrption-)
>[!NOTE]
>Kevlar is not secure at this moment

---

+ Kevlar Encryption is a lighweight encryption software; it is the spiritual successor to OGRE Encryption[^1]. 
  
+ Kevlar is inspired by RSA and ElGammal encryptions and is an asymmetrical encryption.

+ [Monolithic ARM Kernel Project can be found here](https://github.com/GusBallmanjr/ARM-Monolithic-Kernel)

## To Install
If using ssh, then use the ssh clone command.
```
git clone https://github.com/mrthomaslibrary/kevlar-encryption.git
cd kevlar-encryption 
make install
```
---
# Documentation
```
Kevlar Encryption
    Create Keys     |   -c <key-names>
    Encrypt File    |   -e <plaintext> <public-key> <outfile-name>
    Decrypt File    |   -d <encrypted-file> <private-key> <outfile-name>
    Help            |   -h Prints This Message
```



---

[^1]: OGRE Encryption was a lightweight file‑encryption software written for the 2026 CrimsonCode Hackathon using C++, SFML, and our own integer‑safe math. The goal was to create a simple, fast, fully offline tool where the user can drag in a file, enter a password, and encrypt or decrypt it instantly.  Kevlar Encryption aims to succeed where the OGRE software failed. Kevlar Encryption focuses on integration rather than user aesthetic. Kevlar will become the encryption software integrated into the monolithic ARM kernel project (This is one of the reasons why Kevlar is written in C as opposed to C++ as was OGRE).
