
## Überprüfung der Integrität von NEP-Schnittstellen

### Konfiguration

* Detektor-ID: `nep${id}-interface` (`${id}` ist die NEP-ID)
* Schweregrad: mittel

### Beschreibung

[NEPs](https://github.com/near/NEPs) stehen für Near Enhancement Proposals, welche Änderungen an der Spezifikation und den Standards des NEAR-Protokolls darstellen. Derzeit gibt es NEPs für FT, NFT, MT und Storage, die in einer [Tabelle](https://github.com/near/NEPs#neps) aufgelistet sind.

Um diesen Detektor zu nutzen, müssen Sie die NEP-ID in der Detektor-ID spezifizieren, zum Beispiel:

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Fungible Token Standard
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # Storage Management
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Non-Fungible Token Standard
```

### Beispielcode

Das [Beispiel](/examples/nep-interface/) für den Detektor `nep-interface` ist an die near-contract-standards angepasst.
