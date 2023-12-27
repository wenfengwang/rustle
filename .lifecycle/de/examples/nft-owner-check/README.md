
# Beispiel für den Detektor `nft-owner-check`

Dieses Beispiel basiert auf der Implementierung der [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs). Die Überprüfung des Eigentümers in der Funktion [`nft_revoke_all`](src/lib.rs#L171) wurde jedoch entfernt. Das Interface wird unsicher, da nun jeder diese Funktion aufrufen kann, um alle Genehmigungen für den NFT zu widerrufen.
