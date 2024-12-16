import os
import json

with open(os.getcwd() + '\Saved\Automation\Reports\index.json', encoding='utf-8-sig') as json_file:
    json_data = json.loads(json_file.read())
    tests = json_data["tests"]

    successes = []
    failures = []

    for test in tests:
        if test["state"] != "Success":
            print(test["testDisplayName"])
            print(test["state"])
            print("\n")

        if test["state"] == "Success":
            successes.append(test["testDisplayName"])
        else:
            failures.append(test["testDisplayName"])

    print("Tests passed: " + str(len(successes)))
    print("Tests failed: " + str(len(failures)))
