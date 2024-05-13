import sys

import os
import glob

MODULE_DIR: str = os.path.dirname(os.path.realpath(__file__))

def can_build(env, platform) -> bool:
	return True

def configure(env):
	pass

# TOOK OVER AN HOUR FOR THE MOST BASIC CODE
# GOT TYPE ERROR AFTER TYPE ERROR
# TYPE ERRORS ARE EQUALLY AS BAD AS THE RUST COMPILER
def get_doc_classes() -> list:
	print("[Abysseners] Fetching doc files...")
	try:
		docs = []
		glob_data = MODULE_DIR + "/" + get_doc_path() + "/*.xml"
		return glob.glob(glob_data)
	except:
		type, value, traceback = sys.exc_info()
		print("[Abysseners] The module did a fucky wucky of type %s" % type)
		print("\tvalue: %s" % value)
	return []

def get_doc_path() -> str:
	return "doc_classes"