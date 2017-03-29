open Solvuu_build.Std

let project_name = "DockBlock"
let version = "dev"

let mylib = Project.lib project_name
  ~dir:"src"
  ~style:`Basic

let () = Project.basic1 ~project_name ~version [mylib]