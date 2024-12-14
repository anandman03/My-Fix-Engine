import random

# List of currency pairs
currency_pairs = [
    "EUR/USD", "USD/JPY", "GBP/USD", "AUD/USD", "USD/CAD", 
    "USD/CHF", "NZD/USD", "EUR/GBP", "EUR/JPY", "GBP/JPY"
]

# Function to generate a FIX message
def generate_fix_message(message_id, currency_pair, bid_price, ask_price, bid_size, ask_size):
    return (
        f"8=FIX.4.4|9=178|35=W|34={message_id}|49=SenderCompID|56=TargetCompID|"
        f"52=20241214-12:00:00.000|55={currency_pair}|"
        f"268=2|269=0|270={bid_price:.4f}|271={bid_size}|"
        f"269=1|270={ask_price:.4f}|271={ask_size}|10=000|"
    )

# Generate 10,000 FIX messages
messages = []
for i in range(1, 10001):
    currency_pair = random.choice(currency_pairs)
    bid_price = random.uniform(1.0, 1.5)  # Example bid price range
    ask_price = bid_price + random.uniform(0.0001, 0.0010)  # Example spread
    bid_size = random.randint(100000, 1000000)  # Bid size
    ask_size = random.randint(100000, 1000000)  # Ask size
    fix_message = generate_fix_message(i, currency_pair, bid_price, ask_price, bid_size, ask_size)
    messages.append(fix_message)

# Write messages to a file
with open("fix_messages.txt", "w") as file:
    file.write("\n".join(messages))

print("10,000 FIX messages have been generated and saved to 'fix_messages.txt'.")
