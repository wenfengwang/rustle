
# Beispiel für den `nft-approval-check`-Detektor

Dieses Beispiel basiert auf der Implementierung der [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs). Es wurde jedoch eine neue Funktion [`internal_transfer_unsafe`](src/lib.rs#L256) hinzugefügt. In dieser Funktion wird die Überprüfung der `approval_id` entfernt, was nicht korrekt ist.

Die Schnittstelle `nft_transfer` wird diese neue unsichere Funktion `internal_transfer_unsafe` aufrufen, während `nft_transfer_call` weiterhin den sicheren `internal_transfer` nutzen wird. Deshalb wird **Rustle** den `nft_transfer` als unsichere Methode kennzeichnen.
