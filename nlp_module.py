import spacy

class NLPModule:
    def __init__(self):
        self.nlp = spacy.load("en_core_web_sm")

    def process_input(self, input_text):
        doc = self.nlp(input_text)
        intent = None
        entities = []

        for token in doc:
            if token.ent_type_:
                entities.append((token.ent_type_, token.text))

        return {
            "intent": intent,
            "entities": entities
        }

nlp_module = NLPModule()



