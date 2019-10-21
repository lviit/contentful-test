[%raw "require('isomorphic-fetch')"];
[%raw "require('dotenv').config()"];

/*
[@bs.module "dotenv"] external dotenvConfig: unit => unit = "config";
let foo = dotenvConfig();
Js.log(foo);
*/

open Request;
open Js.Promise;
open Json.Decode;

/* make the express app */
let app = Express.App.make();

type fieldsType = {title: string};
type entryType = {fields: fieldsType};

let fieldJson = (json): fieldsType => {title: json |> field("title", string)};
let entryJson = (json): entryType => {fields: json |> field("fields", fieldJson)};

let renderHTML = (_next, _req, res) => {
  let uid = "1HR1QvURo4MoSqO0eqmUeO";

  GetEntry(uid)->request
  |> then_(Fetch.Response.json)
  |> then_(json => {
       Js.log(json);
       let data = json->entryJson;

       let content = ReactDOMServerRe.renderToString(<App title={data.fields.title} />);
       Express.Response.sendString(content, res)->resolve;
     });
};

renderHTML |> Express.PromiseMiddleware.from |> Express.App.useOnPath(~path="/", app);

let port = 3000;

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log("listening at localhost:" ++ string_of_int(port))
  };

Express.App.listen(app, ~onListen, ~port, ());