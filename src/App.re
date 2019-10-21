[@react.component]
let make = (~title) => {
  <div> {ReasonReact.string(title)} </div>;
};