[@bs.val] external accessToken : string = "process.env.ACCESS_TOKEN";
[@bs.val] external apiBaseUrl : string = "process.env.API_BASE_URL";

type request =
  | GetEntry(string);

let requestBase = (endpoint: string, method: Fetch.requestMethod) =>
  Fetch.RequestInit.make(
    ~headers=Fetch.HeadersInit.make({"Authorization": "Bearer " ++ accessToken}),
    ~method_=method,
    (),
  )
  |> Fetch.fetchWithInit(apiBaseUrl ++ endpoint);

let request = (request) =>
  switch (request) {
  | GetEntry(uid) => requestBase("/entries/" ++ uid, Get)
  };
