import logging
import sys
formatter_print =  logging.Formatter('[pirate] %(levelname)-8s %(asctime)s | %(message)s', datefmt=' %H:%M:%S')
formatter_file = logging.Formatter('[pirate][%(levelname)-8s][%(asctime)s]%(message)s')

l = logging.getLogger("test")

# Add a file logger
f = logging.FileHandler("test.log")
f.setFormatter(formatter_file)
l.addHandler(f)

# Add a stream logger
s = logging.StreamHandler(sys.stdout)
s.setFormatter(formatter_print)
l.addHandler(s)

# Send a test message to both -- critical will always log
l.setLevel(logging.INFO)

print("Created logger component with the name of 'l', ,use ist with l.info('messge') l.debug l.error")
l.critical("test log 'critical'")
l.info("test log 'info'")
l.debug("test log 'debug'")