#pragma once
#include <cmath>

namespace FunctionProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        Form1(void)
        {
            InitializeComponent();
        }

    protected:
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblAuthor;
        System::Windows::Forms::Label^ lblX;
        System::Windows::Forms::TextBox^ txtX;
        System::Windows::Forms::Button^ btnCalc;
        System::Windows::Forms::Button^ btnClear;
        System::Windows::Forms::TextBox^ txtResult;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblAuthor = (gcnew System::Windows::Forms::Label());
            this->lblX = (gcnew System::Windows::Forms::Label());
            this->txtX = (gcnew System::Windows::Forms::TextBox());
            this->btnCalc = (gcnew System::Windows::Forms::Button());
            this->btnClear = (gcnew System::Windows::Forms::Button());
            this->txtResult = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();

            // lblTitle
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10,
                System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblTitle->Location = System::Drawing::Point(10, 10);
            this->lblTitle->Name = L"lblTitle";
            this->lblTitle->Size = System::Drawing::Size(280, 17);
            this->lblTitle->TabIndex = 0;
            this->lblTitle->Text = L"Проект: Обчислення значення функції";

            // lblAuthor
            this->lblAuthor->AutoSize = true;
            this->lblAuthor->Location = System::Drawing::Point(10, 35);
            this->lblAuthor->Name = L"lblAuthor";
            this->lblAuthor->Size = System::Drawing::Size(135, 13);
            this->lblAuthor->TabIndex = 1;
            this->lblAuthor->Text = L"Автор: Граждан Тімур";

            // lblX
            this->lblX->AutoSize = true;
            this->lblX->Location = System::Drawing::Point(10, 70);
            this->lblX->Name = L"lblX";
            this->lblX->Size = System::Drawing::Size(52, 13);
            this->lblX->TabIndex = 2;
            this->lblX->Text = L"Введіть x:";

            // txtX
            this->txtX->Location = System::Drawing::Point(80, 67);
            this->txtX->Name = L"txtX";
            this->txtX->Size = System::Drawing::Size(120, 20);
            this->txtX->TabIndex = 3;

            // btnCalc
            this->btnCalc->Location = System::Drawing::Point(10, 110);
            this->btnCalc->Name = L"btnCalc";
            this->btnCalc->Size = System::Drawing::Size(90, 30);
            this->btnCalc->TabIndex = 4;
            this->btnCalc->Text = L"Обчислити";
            this->btnCalc->UseVisualStyleBackColor = true;
            this->btnCalc->Click += gcnew System::EventHandler(this, &Form1::btnCalc_Click);

            // btnClear
            this->btnClear->Location = System::Drawing::Point(110, 110);
            this->btnClear->Name = L"btnClear";
            this->btnClear->Size = System::Drawing::Size(90, 30);
            this->btnClear->TabIndex = 5;
            this->btnClear->Text = L"Очистити";
            this->btnClear->UseVisualStyleBackColor = true;
            this->btnClear->Click += gcnew System::EventHandler(this, &Form1::btnClear_Click);

            // txtResult
            this->txtResult->Location = System::Drawing::Point(10, 160);
            this->txtResult->Multiline = true;
            this->txtResult->Name = L"txtResult";
            this->txtResult->ReadOnly = true;
            this->txtResult->Size = System::Drawing::Size(260, 80);
            this->txtResult->TabIndex = 6;

            // Form1
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(284, 261);
            this->Controls->Add(this->txtResult);
            this->Controls->Add(this->btnClear);
            this->Controls->Add(this->btnCalc);
            this->Controls->Add(this->txtX);
            this->Controls->Add(this->lblX);
            this->Controls->Add(this->lblAuthor);
            this->Controls->Add(this->lblTitle);
            this->Name = L"Form1";
            this->Text = L"Обчислення функції";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        // Обробник кнопки "Обчислити"
        System::Void btnCalc_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try
            {
                // Перевірка: чи введено число
                double x;
                if (!Double::TryParse(txtX->Text, x))
                {
                    MessageBox::Show(L"Помилка: введіть коректне число.");
                    return;
                }

                // Перевірка області визначення:
                // ln(x) існує лише для x > 0
                if (x <= 0)
                {
                    MessageBox::Show(L"ln(x) визначено лише для x > 0.");
                    return;
                }

                // Перевірка: знаменник не повинен дорівнювати нулю
                double denom2 = x * Math::Log(x) - 2 * Math::Pow(Math::Sin(x), 2);
                if (Math::Abs(denom2) < 1e-12)
                {
                    MessageBox::Show(L"Помилка: другий знаменник дорівнює нулю.");
                    return;
                }

                // Обчислення частин виразу
                double term1 = (2 * Math::Pow(Math::Cos(x), 2)) / (1 + x * Math::Cos(2 * x));
                double term2 = Math::Pow(0.3, x) / denom2;

                double y = term1 + term2;

                // Виведення результату
                txtResult->Text = "Результат y = " + y.ToString("F6");
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Сталася помилка при обчисленні: " + ex->Message);
            }
        }

        // Кнопка "Очистити"
        System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e)
        {
            txtX->Clear();
            txtResult->Clear();
            txtX->Focus();
        }
    };
}