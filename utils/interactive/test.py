# Usage: `local_testing_tool.py test_number`, where the argument test_number
# is 0 (Test Set 1), 1 (Test Set 2) or 2 (Test Set 3).

import sys
import random

T = 10
Qs = 30 # change query number here


def GenCase(): # gen cases here
  r = [0] * 2
  r[0] = random.randint(0, 2**29 - 1)
  r[1] = random.randint(r[0] + 1, 2**29)
  return tuple(r)


def GenCases():
  return tuple(GenCase() for _ in range(T))


class Error(Exception):
  pass


class JudgeError(Exception):
  pass


CORRECT, WRONG = 1, -1
INVALID_LINE_ERROR = "Couldn't read a valid line"
TOO_LONG_LINE_ERROR = "Line too long: {} characters".format
WRONG_NUM_TOKENS_ERROR = "Wrong number of tokens, expected 3 or {} got {}".format
NOT_INTEGER_ERROR = "Not an integer: {}".format
OUT_OF_BOUNDS_ERROR = "{} is out of bounds".format
REPEATED_INTEGERS_ERROR = "Received repeated integers: {}".format
TOO_MANY_QUERIES_ERROR = "Queried too many times"
WRONG_ORDER_ERROR = "Guessed wrong order"
CASE_ERROR = "Case #{} failed: {}".format
EXCEPTION_AFTER_END_ERROR = (
    "Exception raised while reading input after all cases finish.")
ADDITIONAL_INPUT_ERROR = "Additional input after all cases finish: {}".format
QUERIES_USED = "Total Queries Used: {}/{}".format


def ParseInteger(line):
  try:
    return int(line)
  except:
    raise Error(NOT_INTEGER_ERROR(line))


def Output(line):
  try:
    print(line)
    sys.stdout.flush()
  except:
    # If we let stdout be closed by the end of the program, then an unraisable
    # broken pipe exception will happen, and we won't be able to finish
    # normally.
    try:
      sys.stdout.close()
    except:
      pass


def RunCase(case, max_q): # do stuff here

  def Input():
    try:
      return input()
    except:
      raise Error(INVALID_LINE_ERROR)

  q = 0
  while True:
    line = Input()
    tokens = line.split()
    if len(tokens) < 2:
      raise Error(WRONG_NUM_TOKENS_ERROR)
    sign = tokens[0]
    if tokens[0] == '!':
      if len(tokens) != 3:
        raise Error(WRONG_NUM_TOKENS_ERROR)
      a, b = (ParseInteger(i) for i in tokens[1:3])
      if a != case[0] or b != case[1]:
        print("got {} {}, expected {} {}".format(a, b, case[0], case[1]), file=sys.stderr)
        raise Error(WRONG)
      return q
    num = ParseInteger(tokens[1])
    if q >= max_q:
      print("expected {} {}".format(case[0], case[1]), file=sys.stderr)
      raise Error(TOO_MANY_QUERIES_ERROR)
    q += 1
    Output((case[0] + num) ^ (case[1] + num))


def RunCases(cases, max_q):
  Output("{}\n{}".format(len(cases), max_q))
  tot_q = 0
  for i, case in enumerate(cases, 1):
    try:
      q = RunCase(case, Qs)
      Output(CORRECT)
      tot_q += q
    except Error as err:
      Output(WRONG)
      raise Error(CASE_ERROR(i, err))

  try:
    extra_input = input()
  except EOFError:
    return tot_q
  except Exception:  # pylint: disable=broad-except
    raise Error(EXCEPTION_AFTER_END_ERROR)
  raise Error(ADDITIONAL_INPUT_ERROR(extra_input[:100]))


def main():
  assert len(sys.argv) == 1, "Bad usage"
  random.seed(1234)
  try:
    q = RunCases(GenCases(), Qs)
    print(QUERIES_USED(q, Qs), file=sys.stderr)
  except Error as err:
    print(str(err)[:1000], file=sys.stderr)
    sys.exit(1)
  except Exception as exception:
    Output(WRONG)
    print(
        ("JUDGE_ERROR! Internal judge exception: {}".format(exception))[:1000],
        file=sys.stderr)
    sys.exit(1)


if __name__ == "__main__":
  main()
