# RCE as a Service (Stage 1)
## Details
- Category: Web
- Author: GEBIRGE

## Description

Cloud computing is trending? Says your **grandpa**!

`Edge Computing` is the future! And the future is now. Today!

Give us a lambda and an array to operate on and our modern `.NET6`-powered backend will compute the results on an edge near your user in *no time*.

But please don't try to run custom code, because [this incident will be reported](https://imgs.xkcd.com/comics/incident.png).

(Goal: Read `flag.txt` at the filesystem's root.)

## Solution

You can have a look at `curl.org` for possible solution payloads.

Hints for players:

Our endpoint `/rce` takes a query in the form of a [lambda expression]((https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/operators/lambda-expressions)) and a string array to operate on.

Otherwise I've written extensively about it [here](https://gebir.ge/blog/privesc-part-1/) and [here](https://gebir.ge/blog/privesc-part-2/).



