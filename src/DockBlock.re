type parsedValues = {mutable text: string, mutable params: list (string, string)};

let startPattern = Re_perl.compile_pat ".*\\/\\*\\*";

let paramPattern = Re_perl.compile_pat ".*\\*.*@([A-Za-z]+) (.*)";

let endPattern = Re_perl.compile_pat ".*\\*\\/";

let rec parseText lines accumulator :parsedValues =>
  switch lines {
  | [] => accumulator
  | [hd, ...tl] =>
    if (Re.execp endPattern hd) {
      parseFile tl accumulator
    } else if (Re.execp paramPattern hd) {
      parseParam lines accumulator
    } else {
      let altText = Re.split (Re_perl.compile_pat "\\* ") hd;
      let last = List.hd (List.rev altText);
      accumulator.text = String.concat "\n" [accumulator.text, last];
      parseText tl accumulator
    }
  }
and parseFile lines accumulator :parsedValues =>
  switch lines {
  | [] => accumulator
  | [hd, ...tl] => Re.execp startPattern hd ? parseText tl accumulator : parseFile tl accumulator
  }
and parseParam lines accumulator :parsedValues =>
  switch lines {
  | [] => accumulator
  | [hd, ...tl] =>
    if (Re.execp paramPattern hd) {
      let groups = Re.exec paramPattern hd;
      let paramName = Re.Group.get groups 1;
      let paramValue = Re.Group.get groups 2;
      accumulator.params = accumulator.params @ [(paramName, paramValue)]
    };
    parseText tl accumulator
  };

let parseBlock words => {
  let accumulator = {text: "", params: []};
  parseFile words accumulator
};
