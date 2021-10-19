import whois
import nslookup as nsl
import random
import requests

valid_commands = {"hello": "Displays a personalized greeting.",
                  "users": "Displays information about the number of users.",
                  "whois <url address>" : "Querying and parsing of domain registration information.",
                  "nslookup <url address>" : "Sensible high-level DNS lookups in Python, using dnspython dns.resolver.",
                  "dice <numbers of wall on one dice> <number of dice toss>": "Throw a dice. <default 6 (max 100)> <default 1 (max 12)>.",
                  "math <operation to calculate>" : "Mathematical calculations.",
                  "curr <quantity> <from currency> <to currency>" : "Calculate currency conversion using actual currency value by API"}


def read_token():
    with open("token.txt", "r") as f:
        return f.readline().strip()

def whois_func(message):
    domain = message.content[7:]
    try:
        if message.content != "8.8.8.8" and whois.whois(domain)["domain_name"] != None:
            return message.channel.send(f'```{whois.whois(domain).text.split("For more information on Whois")[0]}```')
        else:
            return message.channel.send('```Sorry, cannot find website: "{}"```'.format(domain))
    except:

        return message.channel.send('```Sorry, cannot find website: "{}"```'.format(domain))

def nslookup_func(message):
    domain = message.content[10:]
    dns_query = nsl.Nslookup(dns_servers=["1.1.1.1"])
    ips_record = dns_query.dns_lookup(domain)
    if len(ips_record.response_full) != 0:
        return message.channel.send(f"```DNS Google:\n{ips_record.response_full[0]}\n\nDNS OpenDNS:\n{ips_record.answer[0]}```")
    else:
        return message.channel.send(f'```Domain: "{domain}" not exist.```')

def help_func(message):
    txt = "```To use command, write '!' before command\n\n"
    for k, v in valid_commands.items():
        txt += f"{k} --> {v}\n"
    txt += "```"
    return message.channel.send(txt)

def dice_throw(message):
    MIN_THROW = 1
    MAX_THROW = 12
    MIN_WALLS = 4
    MAX_WALLS = 100
    n = message.content[6:].split()
    if len(n) == 0:
        return message.channel.send(f"```Throw 1:\t{random.randint(1, 6)}```")
    elif len(n) == 1:
        if int(n[0]) < MIN_WALLS or int(n[0]) > MAX_WALLS:
            return message.channel.send(f"```Wall on dice: 4 - 100 (not {int(n[0])})```")
        else:
            return message.channel.send(f"```Throw 1:\t{random.randint(1, int(n[0]))}```")
    elif len(n) == 2:
        if int(n[0]) < MIN_WALLS or int(n[0]) > MAX_WALLS:
            return message.channel.send(f"```Wall on dice: 4 - 100 (not {int(n[0])})```")
        elif int(n[1]) < MIN_THROW or int(n[1]) > MAX_THROW:
            return message.channel.send(f"```Number of dice throws: 1 - 12 (not {int(n[1])})```")
        else:
            li = [random.randint(1, int(n[0])) for x in range(1, int(n[1]) + 1)]
            txt = []
            for n, v in enumerate(li):
                txt.append("Throw {:>2}: {:>3}".format(n + 1, v))
            txt.append(" ")
            txt.append("Sum: {:>5}".format(sum(li)))
            new_text = '\n'.join(txt)
            return message.channel.send(f"```{new_text}```")
    elif len(n) >= 3:
        return message.channel.send("```Too many arguments (max: 2)```")

def math_func(message):
    operation = str(message.content)[5:]
    try:
        result = eval(operation)
        return message.channel.send(f"```Operation: {operation}\nResult: {result}```")
    except:
        return message.channel.send(f"```Sorry, I can't compute: {operation}```")

def currency_exchange_calculator(message):
    with open("currency_dict.txt", "r", encoding="utf-8") as f:
        curr_dict = eval(f.readline())
    txt = message.content.split()
    from_amount = "".join(txt[1:-2])
    currencies = [txt[-2].strip(), txt[-1].strip()]
    values = []
    if not from_amount.isnumeric():
        return message.channel.send(f"```Wrong amount: {txt[1:-1][0]}```")
    else:
        from_amount = float(from_amount)
        if currencies[0] == currencies[1]:
            return message.channel.send("```Currencies cannot be the same.```")
        else:
            for c in currencies:
                if c == "pln":
                    values.append(1)
                elif c in curr_dict:
                    if requests.get("https://api.nbp.pl/api/exchangerates/rates/a/{}".format(c)).status_code == 404:
                        value = requests.get("https://api.nbp.pl/api/exchangerates/rates/b/{}".format(c)).json()["rates"][0]["mid"]
                    else:
                        value = requests.get("https://api.nbp.pl/api/exchangerates/rates/a/{}".format(c)).json()["rates"][0]["mid"]
                    values.append(value)
                else:
                    return message.channel.send(f"```Wrong currency: {c}\nFor more information use '!currhelp'```")
            if currencies[1] == "pln":
                result = from_amount * values[0]

            else:
                result = from_amount * values[0] / values[-1]
            return message.channel.send(f"```{from_amount} {currencies[0]} = {round(result, 2)} {currencies[1]}```")

def currencies_codes(message, start, stop):
    with open("currency_dict.txt", "r", encoding="utf-8") as f:
        curr_dict = eval(f.readline())
        final_list = [("{:>29} - {:}".format(curr_name, code)) for curr_name, code
                                in sorted({v:k for k, v in curr_dict.items()}.items())]
        final_list = final_list[start:stop]
        final_list = "\n".join(final_list)
        return message.channel.send(f"```{final_list}```")

