let docBlockPattern = Str.regexp ".*\\/\\*\\*";

let innerParse docString => {
  let lines = Str.split (Str.regexp "\n") docString;
  DockBlock.parseBlock lines
};

let parse docString => {
  let location =
    try (Str.search_forward docBlockPattern docString 0) {
    | Not_found => (-1)
    };
  location >= 0 ? innerParse docString : {text: "", params: []}
};
