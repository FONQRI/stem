# ArioServer

A webServer application based on [H2O](https://github.com/h2o/h2o)

## Getting Started

After installing dependencies you can run project and see output in localhost:7890

### Prerequisites

What things you need to install the software and how to install them

* [CMake](https://cmake.org)
* [Boost](https://www.boost.org)
* [H2O](https://github.com/h2o/h2o)
* [Inja](https://github.com/pantor/inja)
* [Mongodb server](https://www.mongodb.com/download-center/community)
* [Mongocxx](https://github.com/mongodb/mongo-cxx-driver)

### Building

```
cmake -Bbuild -H. && cd build && make -j9
```
Or open with qtcreator and click run button.

### Installing

Not compeleted yet.

## Running the tests

After running see http://localhost:7890/

## Deployment

If you need to develope this project you need to add a function like below :
```
int home_service_handler(h2o_handler_t *self, h2o_req_t *req)
```

And register it with a path like below:

```
register_handler(hostconf, "/", ario::home_service_handler);
```

And you need to work on this handler function.

## Built With

* [CMake](https://cmake.org)
* [Boost](https://www.boost.org)
* [H2O](https://github.com/h2o/h2o)
* [Inja](https://github.com/pantor/inja)
* [Mongodb server](https://www.mongodb.com/download-center/community)
* [Mongocxx](https://github.com/mongodb/mongo-cxx-driver) Used to generate RSS Feeds

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Bhenam Sabbaghi** - *Initial work* - [FONQRI](https://github.com/FONQRI)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
