import discord
from functions import *

client = discord.Client()

@client.event
async def on_member_join(member):
    for channel in member.server.channels:
        if str(channel) == "general":
            await client.send_message("Hello {}!".format(member.mention))


@client.event
async def on_message(message):
    id_ = client.get_guild(891305047672123474) # discord app server settings
    if message.content == "!hello":
        await message.channel.send(f"```Ohayou {str(message.author).split('#')[0]}!```")

    elif message.content == "!users":
        await message.channel.send("```Number of Members: {}```".format(id_.member_count))

    elif "!whois " in message.content:
        await whois_func(message)

    elif "!nslookup " in message.content:
        await nslookup_func(message)

    elif message.content == "!help":
        await help_func(message)

    elif "!dice" in message.content:
        await dice_throw(message)

    elif "!math " in message.content:
        await math_func(message)

    elif "!curr " in message.content:
        await currency_exchange_calculator(message)

    elif message.content == "!currhelp":
        await currencies_codes(message, 0, 48)
        await currencies_codes(message, 48, 96)
        await currencies_codes(message, 96, 144)

client.run(read_token())

