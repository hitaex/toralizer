
# Toralize!

**Toralize** is a script designed to help maintain your anonymity while using various applications.

## How to Use

Simply prepend `toralize` to any command to run it with Tor anonymization:

```sh
toralize firefox
```

## Dependencies

Make sure you have the following dependencies installed:

- **Tor**
- **GCC**

## Installation

To install Toralize, follow these steps:

1. Clone the repository and navigate into the directory:

    ```sh
    git clone https://github.com/hitaex/toralize.git && cd toralize
    ```

2. Compile the project:

    ```sh
    make
    ```

3. Create the `toralize` script and move it to `/usr/bin/`:

    ```sh
    echo '#!/bin/zsh
    export LD_PRELOAD=path/to/toralizer/toralize.so
    "${@}"
    unset LD_PRELOAD' | sudo tee /usr/bin/toralize > /dev/null
    ```
OR if you use Bin (Default):
 ```sh
    echo '#!/bin/bin
    export LD_PRELOAD=/path/to/toralizer/toralize.so
    "${@}"
    unset LD_PRELOAD' | sudo tee /usr/bin/toralize > /dev/null
    ```

4. Set the appropriate permissions for the script:

    ```sh
    sudo chmod 775 /usr/bin/toralize
    ```

Now you can run any command anonymously by using `toralize`!

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](https://www.gnu.org/licenses/gpl-3.0.en.html) file for details.
