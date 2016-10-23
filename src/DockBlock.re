
type parsedValues = {mutable text: string, mutable params: list (string, string)};

let docBlockPattern = Str.regexp ".*\\/\\*\\*";

let paramPattern = Str.regexp ".*\\*.*@\\([A-Za-z]+\\) \\(.*\\)";

let endPattern = Str.regexp ".*\\*\\/";

let rec parseText (lines, accumulator: parsedValues) =>
  switch lines {
  | [] => accumulator
  | [hd, ...tl] =>
    if (Str.string_match endPattern hd 0) {
      parseFile (tl, accumulator)
    } else if (
      Str.string_match paramPattern hd 0
    ) {
      parseParam (lines, accumulator)
    } else {
      let text = Str.split (Str.regexp "\\* ") hd;
      let last = List.hd (List.rev text);
      accumulator.text = String.concat "\n" [accumulator.text, last];
      parseText (tl, accumulator)
    }
  }
and parseFile (lines, accumulator: parsedValues) =>
  switch lines {
  | [] => accumulator
  | [hd, ...tl] =>
    Str.string_match docBlockPattern hd 0 ?
      parseText (tl, accumulator) : parseFile (tl, accumulator)
  }
and parseParam (lines, accumulator: parsedValues) =>
  switch lines {
  | [] => accumulator
  | [hd, ...tl] =>
    if (Str.string_match paramPattern hd 0) {
      let paramName = Str.matched_group 1 hd;
      let paramValue = Str.matched_group 2 hd;
      print_endline (String.concat " | " [paramName, paramValue]);
      accumulator.params = accumulator.params @ [(paramName, paramValue)]
    };
    parseText (tl, accumulator)
  };

let parseBlock words => {
  let accumulator = {text: "", params: []};
  parseFile (words, accumulator)
};
