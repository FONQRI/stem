# Why ?

## Data Model
Existing choises:
   * Json
   * Avro
   * thrift
   * portocol buffer
Choosing Json because it's a general purpose data model and it can be generated in any platform and there is enough library in all languages for that makes it good for user interface and if we use another data model for backend cost of parsing json to that data model would be waste.
And for library i chosed [nlohmann/json](https://github.com/nlohmann/json) because it has good benchmark at [nativejson-benchmark](https://github.com/miloyip/nativejson-benchmark) and it has a big comunity to support it.
