#ifndef JC_CHECK_HPP
#define JC_CHECK_HPP

namespace jc
{
    class Check
    {
      public:
        Check() : result_{true} {}

        void add(bool result) { result_ &= result; }

        int returnValue() const { return result_ ? 0 : 1; }

      private:
        bool result_;
    };
}

#endif // !JC_CHECK_HPP
