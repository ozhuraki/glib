# Copyright © 2023, Intel Corporation.
# SPDX-License-Identifier: ISC

import sys
import json
from gi.repository import GObject

class MyObject(GObject.GObject):

    def __init__(self):
        GObject.GObject.__init__(self)

def main():
    GObject.type_register(MyObject)

    obj = MyObject()

    print(json.dumps(obj.__dict__))

    sys.exit(0)

if __name__ == '__main__':
    main()

