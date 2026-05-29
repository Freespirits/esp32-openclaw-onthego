# Getting Started

Use this guide to connect an ESP32 board from this repository to an existing Mochi gateway.

## What You Need

- Mochi installed and `mochi` available on `PATH`
- An Mochi gateway the board can reach
- ESP-IDF `5.x`
- An ESP32 board with Wi-Fi
- A serial connection or board-specific flashing path, depending on the example

Commands below assume the default Mochi install. If you use a named profile, add `--profile <profile>` to the `mochi` commands.

## Choose An Example

- [ESP32 Wi-Fi Node Example](../examples/esp32-node/README.md): Generic ESP32 node with Wi-Fi, GPIO, and ADC commands.
- [ESP-BOX-3 Display Example](../examples/esp-box-3-display/README.md): ESP-BOX-3 node with Wi-Fi and display commands for the built-in screen.

## Prepare The Gateway

If the board will connect over Wi-Fi to a gateway running on another machine, set `gateway.bind` to `lan` first. The default loopback bind is only reachable from the gateway host itself.

Before pairing a board, set `gateway.nodes.allowCommands` for the example you are using. Each example README lists the commands to allow.

```bash
mochi config set gateway.bind lan
mochi config set gateway.nodes.allowCommands '<json-array-from-example>' --strict-json
mochi gateway restart
mochi gateway status --probe --json
```

If the gateway stays on loopback, the board cannot reach it over Wi-Fi. If the gateway does not allow the example's commands, the node can connect and still show `commands: []`.

## Build And Flash

Use the commands from the example README for the board you are using. The general flow is:

```bash
. ~/esp-idf/export.sh
cd /path/to/example
idf.py set-target <target>
idf.py build
idf.py -p <serial-port> flash monitor
```

## Pair The Board With The Gateway

Use a setup code for the first connection, or one of the other explicit auth
commands described below.

Generate one on the gateway host:

```bash
mochi qr \
  --url ws://<gateway-host-ip>:<gateway-port> \
  --setup-code-only
```

The command prints a single setup code:

```text
<setup-code>
```

Sample setup code:

```text
eyJ1cmwiOiJ3czovLzE5Mi4xNjguMS4xMDoxODc4OSIsImJvb3RzdHJhcFRva2VuIjoib2NfYm9vdHN0cmFwX2V4YW1wbGVfdG9rZW4ifQ
```

If the installed gateway already resolves the correct LAN URL, you can omit `--url`. 

After flashing, open the serial console for the board and use the REPL:

```text
mochi> status
mochi> wifi set <ssid> <passphrase>
mochi> gateway setup-code <setup-code>
mochi> status
```

Each example README calls out the console path for that board and the commands it exposes after pairing.

- Use `wifi set <ssid>` for an open network, or `wifi set <ssid> <passphrase>` for a secured network.
- The setup code contains a short-lived `bootstrapToken`, not the gateway's
shared token. `gateway setup-code <setup-code>` requests one explicit connect  
attempt.
- If Wi-Fi is still coming up, the REPL waits for the board to obtain an  
IP before it submits that attempt.
- After a successful `hello-ok`, the node
stores the issued `{ gateway_uri, device_token }` reconnect session and uses it
on later `gateway connect` attempts.

Other first-connect options from the REPL are:

- `gateway token <ws://host:port> <token>`
- `gateway password <ws://host:port> <password>`
- `gateway no-auth <ws://host:port>`

`gateway connect` is only for reconnecting with a saved session that already
exists on the board.

## Check The Node From The Gateway

```bash
mochi nodes status --json
mochi nodes invoke --node <node-id> --command device.info --json
```

Then run one of the commands from the README for the board you are using.

If pairing did not complete as expected, use [Troubleshooting](./troubleshooting.md).

## Troubleshooting And Reference

- [Troubleshooting](./troubleshooting.md)
- [Component README](../components/esp-mochi-node/README.md)

