open Printf
open Solvuu_build.Std

let project_name = "DockBlock"
let version = "dev"

let findlib_deps = [
  "re";
  "ounit";
]

let lib = Project.lib project_name
  ~dir:"src"
  ~style:(`Pack project_name)
  ~findlib_deps

let test : Project.item = Project.app "my-app"
  ~file:"test/test.re"
  ~internal_deps:[lib]

let ocamlinit_postfix = [
  sprintf "open %s" (String.capitalize project_name);
]

;;
let () = Project.basic1 ~project_name ~version [lib;test] ~ocamlinit_postfix