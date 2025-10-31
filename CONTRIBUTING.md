# 🤝 Contributing to RockShield AI

We're thrilled you're interested in contributing to the RockShield AI project! Your help can make this landslide prediction system even better and more robust.

Please take a moment to review this document to ensure a smooth and effective contribution process.

---

## 🌟 How Can I Contribute?

There are many ways to contribute, not just by writing code:

* **Reporting Bugs:** Found a bug in the Arduino code, ML model, or documentation? Please open an [issue](#-reporting-bugs).
* **Suggesting Enhancements:** Have an idea for a new feature, a better sensor, or an improvement to the existing system? Open an [issue](#-proposing-enhancements).
* **Improving Documentation:** Spotted a typo, unclear explanation, or missing detail in the `README.md` or `docs/` folder? Submit a Pull Request with your changes.
* **Code Contributions:** Write code for new features, bug fixes, or performance improvements. See [Submitting a Pull Request](#-submitting-a-pull-request).
* **Testing:** Help us by testing new features or reporting on the reliability of the system in different environments.

---

## 🐛 Reporting Bugs

If you find a bug, please help us by [opening a new issue](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/issues/new?assignees=&labels=bug&projects=&template=bug_report.md&title=).

When reporting a bug, please include as much detail as possible:

* **Project Component:** Which part of the project is affected (e.g., `RockShield_AI.ino`, ML model, `config.h`, documentation)?
* **ESP Board:** Specify your ESP32 model (e.g., ESP32 DevKitC, NodeMCU ESP32).
* **Arduino IDE/PlatformIO Version:**
* **Steps to Reproduce:** A clear, step-by-step description of how to reliably trigger the bug.
* **Expected Behavior:** What you expected to happen.
* **Actual Behavior:** What actually happened.
* **Error Messages:** Any output from the Serial Monitor or console.
* **Screenshots/GIFs:** (Optional) Visual aids are always helpful.

---

## ✨ Proposing Enhancements

Got an idea for an improvement or a new feature? We'd love to hear it! Please [open a new issue](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/issues/new?assignees=&labels=enhancement&projects=&template=feature_request.md&title=).

When suggesting an enhancement, please describe:

* **The Feature/Improvement:** A clear and concise description.
* **The Problem It Solves:** Why is this enhancement needed?
* **Possible Solutions:** Any ideas you have on how it could be implemented.
* **Affected Components:** Which parts of the system would need changes (hardware, firmware, ML model, API)?

---

## 💻 Submitting a Pull Request (Code Contributions)

Before submitting a Pull Request, please ensure you've:

1.  **Forked the Repository:** Fork the `RockShield AI` repository to your own GitHub account.
2.  **Cloned Your Fork:** Clone your forked repository to your local machine.
3.  **Create a New Branch:** Create a new branch for your feature or bug fix.
    * For features: `git checkout -b feature/your-feature-name`
    * For bug fixes: `git checkout -b bugfix/issue-description`
4.  **Make Your Changes:** Implement your changes.
    * **Code Style:** Adhere to the existing coding style in the project. For Arduino, keep it readable and commented. For Python, follow PEP8 guidelines.
    * **Comments:** Add comments to your code, especially for complex logic.
    * **Documentation:** Update the `README.md` or relevant `docs/` files if your changes affect the system's usage, hardware, or ML model.
    * **Testing:** If possible, include information about how you tested your changes.
5.  **Commit Your Changes:** Write clear, concise commit messages.
    * Use the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification (e.g., `feat: Add GPS module`, `fix: Correct DHT sensor reading`).
6.  **Push Your Branch:** Push your new branch to your forked repository on GitHub.
7.  **Open a Pull Request:** Go to the original `RockShield AI` repository on GitHub and open a new Pull Request.
    * **Title:** Use a clear and descriptive title (e.g., `feat: Implement local SD card logging`).
    * **Description:** Provide a detailed description of your changes, why they were made, and any related issues (e.g., `Closes #123`).
    * **Screenshots/GIFs:** Include visual proof if your changes affect the UI or hardware behavior.

---

Thank you for helping to improve RockShield AI!