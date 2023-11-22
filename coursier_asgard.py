from typing import List


class Noeud:
    def __init__(self, nom: str) -> None:
        self.nom = nom
        self.parent: Noeud | None = None
        self.enfants: list[Noeud] = []

    def ajouter(self, enfant: object) -> None:
        enfant.parent = self
        self.enfants.append(enfant)

    def comprend(self, nom: str) -> bool:
        noms: set[str] = set([n.nom for n in self.enfants])
        return nom in noms

    def recuperer(self, nom: str) -> object | None:
        for enfant in self.enfants:
            if enfant.nom == nom:
                return enfant
        return None


def generer_passations_possibles(dieux: list[str], passations: list[str]) -> dict[str, list[str]] | False:
    passations_possibles: dict[str, list[str]] = {dieu: [] for dieu in dieux}

    for passation in passations:
        morceaux: list[str] = passation.split(" ")
        if morceaux[0] != morceaux[2] and morceaux[1] != morceaux[3]:
            return False

        dieu1: str = morceaux[0] + " " + morceaux[1]
        dieu2: str = morceaux[2] + " " + morceaux[3]
        passations_possibles[dieu1].append(dieu2)
        passations_possibles[dieu2].append(dieu1)

    return passations_possibles


def passation_optimale(dieu_actuel: str, passations_possibles: dict[str, list[str]], deja_visites: set[str]) -> str | None:
    prochains_dieux = passations_possibles[dieu_actuel]
    for prochain_dieu in passations_possibles[dieu_actuel]:
        if prochain_dieu in deja_visites:
            prochains_dieux.remove(prochain_dieu)

    if len(prochains_dieux) == 0:
        return None

    plus_isole = prochains_dieux[0]
    for prochain_dieu in prochains_dieux:
        if len(passations_possibles[prochain_dieu]) < len(passations_possibles[plus_isole]):
            plus_isole = prochain_dieu

    return plus_isole


def depart_possible(depart: str, passations_possibles: dict[str, list[str]]) -> bool:
    dernier_dieu: str | None = None
    dieu_actuel: str = depart
    deja_visites: set[str] = set([])

    while True:
        deja_visites.add(dieu_actuel)
        prochain_dieu = passation_optimale(dieu_actuel, passations_possibles, deja_visites)
        if prochain_dieu is None:
            if dernier_dieu is None:
                break
            dieu_actuel = dernier_dieu
            dernier_dieu = None
        dernier_dieu = dieu_actuel
        dieu_actuel = prochain_dieu


def chemin_valide(n: int, dieux: List[str], m: int, passations: List[str]) -> None:
    """
    :param n: le nombre de dieux
    :param dieux: liste des prénoms et noms des dieux séparés par un espace
    :param m: nombre de passations du message
    :param passations: liste des échanges de message entre les dieux, les noms complets des deux dieux séparés par un espace
    """
    # TODO Si le message n'a pas été passé en respectant le protocole, afficher
    # sur une ligne le message `NON`. Sinon, afficher `OUI` sur une ligne,
    # puis, en affichant un nom par ligne, le nom de tous les dieux ayant pu
    # être dieu initial.
    if m < n - 1:
        print("NON")
        return

    passations_possibles = generer_passations_possibles(dieux, passations)
    if not passations_possibles:
        print("NON")
        return

    departs_possibles = {dieu: depart_possible(dieu, passations_possibles) for dieu in dieux}
    if list(departs_possibles.values()).count(True) == 0:
        print("NON")
        return

    print("OUI")
    for depart in departs_possibles:
        print(depart)


if __name__ == "__main__":
    n = int(input())
    dieux = [input() for _ in range(n)]
    m = int(input())
    passations = [input() for _ in range(m)]
    chemin_valide(n, dieux, m, passations)
